#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>
#include <signal.h>

/* Moves the cursor to row x, col y */
#define CUP(x,y) printf("\033[%d;%dH", x,y);
/* Erase in display.
         x=0: Clear from cursor to end of screen
         x=1: Clear from cursor to beginning of screen 
         x=2: Clear entire screen and delete lines in scrollback buffer
*/
#define ED(x) printf("\033[%dJ", x);
/* Moves the cursor the beginning of next line */
#define CNL() printf("\033[E");
/* Display the cursor */
#define CURSHW() printf("\033[?25h");
/* Hide the cursor */
#define CURHID() printf("\033[?25l");
/* Reset terminal color */
#define COLOR_RESET() printf("\033[0m");
struct vector{
	double x;
	double y;
	double z;
};

/* Original Cube verticies */
struct vector const cube[8] = {
    {  1, -1,  1 },   //A
    { -1, -1,  1 },   //B
    { -1,  1,  1 },   //C
    {  1,  1,  1 },   //D
    {  1, -1, -1 },   //E
    { -1, -1, -1 },   //F
    { -1,  1, -1 },   //G
    {  1,  1, -1 }    //H
};

/* Cube verticies */
struct vector cube_rotated[8] = {
    {  1, -1,  1 },   //A
    { -1, -1,  1 },   //B
    { -1,  1,  1 },   //C
    {  1,  1,  1 },   //D
    {  1, -1, -1 },   //E
    { -1, -1, -1 },   //F
    { -1,  1, -1 },   //G
    {  1,  1, -1 }    //H
};

//[0] = A
//[1] = B
//[2] = C
//[3] = D
//[4] = E
//[5] = F
//[6] = G
//[7] = H
struct face {
    struct vector *TL;
    struct vector *TR;
    struct vector *BL;
    struct vector *BR;
} faces[6] = {
    { &cube_rotated[0], &cube_rotated[3], &cube_rotated[4], &cube_rotated[7] },//A D E H
    { &cube_rotated[1], &cube_rotated[0], &cube_rotated[5], &cube_rotated[4] }, // B A F E
    { &cube_rotated[2], &cube_rotated[1], &cube_rotated[6], &cube_rotated[5] }, // C B G F
    { &cube_rotated[3], &cube_rotated[2], &cube_rotated[7], &cube_rotated[6] }, // D C H G
    { &cube_rotated[1], &cube_rotated[2], &cube_rotated[0], &cube_rotated[3] }, // B C A D
    { &cube_rotated[4], &cube_rotated[7], &cube_rotated[5], &cube_rotated[6] }  // E H F G
};

/* Global variables */
char **screenBuff;
static int row;
static int col;

/* Displaying */
int createBuf(int, int);
void printCube(int,int, bool);
void clearBuf(int , int );

/* Rotating */
void rotate(void);

/* Vector */
double dotProd(struct vector v1, struct vector v2);
struct vector crossProd(struct vector v1, struct vector v2);
struct vector calcVec(struct vector v1, struct vector v2);
void scalePt(struct vector *pt, double scale);
void movePt(struct vector *pt, int row, int col);
void projPt(struct vector *pt);

/* Draw Triangle */
void drawTriangle(struct vector a, struct vector b, struct vector c, char ascii);
void drawFlatTop(struct vector a, struct vector b, struct vector c, char ascii);
void drawFlatBot(struct vector a, struct vector b, struct vector c, char ascii);
struct vector nearX(struct vector a, struct vector b);
struct vector nearY(struct vector a, struct vector b);
bool vectorIsEqual(struct vector a, struct vector b);
void checkBnd(int *y, int *x);
void checkVectorBnd(struct vector *pt);
int isFlat(struct vector a, struct vector b, struct vector c);
double getSlope(struct vector a, struct vector b);

/* Auxiallary functions */
void printInfo(void);
char getASCII(int face);
const char* getColor(char);
int _atoi(char*);
void handle_sigint(int);

int main(int argc, char **argv){
	signal(SIGINT, handle_sigint);
	

	if(argc <= 2){
		if( !*(argv + 1) ) {
			printf("How to start program: <Progam> <Screen width> <Screen height> <Cube size> [Optional] -color\nOr use flag -h or -help for info about the program");
			return 0;

		}
		if(!strcmp(*(argv + 1), "-h") || !strcmp(*(argv + 1), "-help")){
			printInfo();
			return 0;
		}
	}

	double distance = 3.5, scale = 20.0;
	struct vector cam ={0,0,1}, cross, v1, v2; 
	int size;
	char buffer[64];
	bool colorSet = false;

	row = _atoi(*(argv + 1));
	col = _atoi(*(argv + 2));
	
	if( argc == 4 ){
		if(!strcmp(*(argv+3), "-color") || !strcmp(*(argv+3), "-c")){
			colorSet = true;
		}else{
			scale = _atoi(*(argv + 3));
		}
	}

	if(argc == 5){
		if(!strcmp(*(argv+4), "-color") || !strcmp(*(argv+4), "-c"))
			colorSet = true;
		scale = _atoi(*(argv + 3));
	
	}
	if(createBuf(row, col) != 0){
		printf("Allocation of screen buffer failed!\n");
		return -1;
	}
	
	CURHID();
	ED(2);
	//TODO: CHange so that the program ONLY cleares cube and prints for terminal
	while(1){
		clearBuf(row, col);
		rotate();	
		size = (int)(sizeof(cube_rotated)/sizeof(cube_rotated[0]));	
		for(int pt = 0; pt < size; pt++){
			/* Push point further along z-axis */
			cube_rotated[pt].z += distance;
			/* Project coordinate from 3D to 2D */
			projPt(&cube_rotated[pt]);
			/* Scale coordinate */
			scalePt(&cube_rotated[pt], scale);
			/* Move from projected 2D plane to terminal */
			movePt(&cube_rotated[pt], row, col);
		}
		
		size = (int)(sizeof(faces)/sizeof(faces[0]));
		for(int i = 0; i < 6; i++){
			v1 = calcVec( *(faces[i].TL), *(faces[i].BL) ); 
			v2 = calcVec( *(faces[i].TL), *(faces[i].TR) ); 
			cross = crossProd(v1, v2);
			if( dotProd(cross, cam) < 0 ){
				drawTriangle(*faces[i].TL, *faces[i].TR, *faces[i].BL, getASCII(i));
				drawTriangle(*faces[i].TR, *faces[i].BR, *faces[i].BL, getASCII(i));
			}
		}
		printCube(row,col, colorSet);

		/* ----------------- INPUT HANDLING --------------- */
		/* File description set variable */
		fd_set fds;
		/* Clear the set */
		FD_ZERO(&fds); 
		/* Add standard input(0) to the set */
		FD_SET(STDIN_FILENO, &fds);
		/* Set timeout to zero */
		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		/* Exit progam if user input 'q' or 'clear' */
		int r = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
		if (r > 0 && FD_ISSET(STDIN_FILENO, &fds)) {
			if (fgets(buffer, sizeof(buffer), stdin)) {
				buffer[strcspn(buffer, "\n")] = '\0';

				if (strcmp(buffer, "clear") == 0 || strcmp(buffer, "q") == 0) {
				break;
				}
			}
		}
		usleep(18500);
	}

	for(int r = 0; r < row; r++)
		free(*(screenBuff + r));
	free(screenBuff);

	CURSHW();
	return 0;
}

/* Allocates memory for screen buffer. Origo on [0,0] */
int createBuf(int row, int col){
	int i;
	screenBuff = (char**)malloc(sizeof(char*) * row);
	if( screenBuff == NULL ) return -1;
	for(i = 0; i < row; i++){
		*(screenBuff + i) = (char*)malloc(sizeof(char) * col);
		if (*(screenBuff + i) == NULL) return -1;
	}
	return 0;
}

/* Rotates the cube by moving the cube verticies */
void rotate(void){
	struct vector v;
	static double angX = 0.0, angY = 0.0, angZ = 0.0;
	double rMatrice[3][3];
	double cosX = cos(angX), sinX = sin(angX);
	double cosY = cos(angY), sinY = sin(angY);
	double cosZ = cos(angZ), sinZ = sin(angZ);

	/* Define rotation matrice */	
	rMatrice[0][0] = cosZ*cosY;
	rMatrice[0][1] = cosZ*sinY*sinX-sinZ*cosX;
	rMatrice[0][2] = cosZ*sinY*cosX +sinZ*sinX;

	rMatrice[1][0] = sinZ*cosY;
	rMatrice[1][1] = sinZ*sinY*sinX+cosZ*cosX;
	rMatrice[1][2] = sinZ*sinY*cosX-cosZ*sinX;

	rMatrice[2][0] = -sinY;
	rMatrice[2][1] = cosY*sinX;
	rMatrice[2][2] = cosY*cosX;

	/* Rotate each vertice */
	for(int i = 0; i < (int)(sizeof(cube) / sizeof(cube[0])); i++){
		v = cube[i];
		cube_rotated[i].x = rMatrice[0][0]*v.x+rMatrice[0][1]*v.y+rMatrice[0][2]*v.z;
		cube_rotated[i].y = rMatrice[1][0]*v.x+rMatrice[1][1]*v.y+rMatrice[1][2]*v.z;
		cube_rotated[i].z = rMatrice[2][0]*v.x+rMatrice[2][1]*v.y+rMatrice[2][2]*v.z;
	}
	/* Float modulus */
	angX = fmod(angX + 0.013, 2*M_PI);
	angY = fmod(angY + 0.025, 2*M_PI);
	angZ = fmod(angZ + 0.036, 2*M_PI);
}

char getASCII(int face){
	switch(face){
		case 0: return '#';
		case 1: return 'o';
		case 2: return '=';
		case 3: return '*';
		case 4: return '%';
		case 5: return '$';
		default: return 'E';
	}
}

void drawTriangle(struct vector a, struct vector b, struct vector c, char ascii){
	struct vector v0,v1,v2,m;

	checkVectorBnd(&a);
	checkVectorBnd(&b);
	checkVectorBnd(&c);

	/* Sort closest to x-axis : [v0, v1, v2] */
	v0 = nearX(a, nearX(b,c));
	if( vectorIsEqual(v0, a) ){
		v1 = nearX(b,c);
		v2 = vectorIsEqual(v1, b) ? c : b; 
		
	}else if( vectorIsEqual(v0, b) ){
		v1 = nearX(a,c);
		v2 = vectorIsEqual(v1, a) ? c : a;
	}else{
		v1 = nearX(a,b);
		v2 = vectorIsEqual(v1,a) ? b : a;
	}
	
	/* Flat top */
	if(v0.y == v1.y){
		drawFlatTop(v0,v1,v2,ascii);
		return;
	/* Flat bot */
	}else if(v1.y == v2.y){
		drawFlatBot(v0,v1,v2, ascii);
		return;
	}
	/* Calculate mid-point m */
	m.x = v0.x + ((v1.y-v0.y)*(v2.x-v0.x)) / (v2.y - v0.y);
	m.y = v1.y;
	
	drawFlatBot(v0,(m.x < v1.x) ? m : v1, (m.x < v1.x) ? v1 : m, ascii);
	drawFlatTop((m.x < v1.x) ? m : v1, (m.x < v1.x) ? v1 : m, v2, ascii);
}

/* 
 * Observe that vectors a,b,c must be sorted by lowest y-val. If two has the same y-val then sort on lowest x-val
 */
void drawFlatTop(struct vector a, struct vector b, struct vector c, char ascii){

	checkVectorBnd(&a);
	checkVectorBnd(&b);
	checkVectorBnd(&c);
	int y;	
	struct vector stPt = a;
	struct vector endPt = b;
	double slopeAC, slopeBC;
	
	if( (slopeAC = getSlope(a,c)) == DBL_MAX){
		//dx = 0
		slopeAC = 0;
	}else if(slopeAC == -DBL_MAX){
		//dy
		return;	
	}
	if( (slopeBC = getSlope(b,c)) == DBL_MAX){
		//dx = 0
		slopeBC = 0;
	}else if(slopeAC == -DBL_MAX){
		//dy = 0
		return;
	}
	
	while(1){
		y = (int)round(stPt.y);
		for(int i = (int)round(stPt.x); i <= (int)round(endPt.x); i++){
			checkBnd(&y, &i);
			screenBuff[y][i] = ascii;
		}
		if( vectorIsEqual(stPt, c)) break;
		stPt.x += slopeAC;
		stPt.y += 1.0;
		endPt.x += slopeBC;
		endPt.y += 1.0;
	}	
}
/* 
 * Observe that vectors a,b,c must be sorted by lowest y-val. If two has the same y-val then sort on lowest x-val
 */
void drawFlatBot(struct vector a, struct vector b, struct vector c, char ascii){
	checkVectorBnd(&a);
	checkVectorBnd(&b);
	checkVectorBnd(&c);
	int y;	
	struct vector stPt = a;
	struct vector endPt = a;
	double slopeAC, slopeAB;
	
	if( (slopeAC = getSlope(a,c)) == DBL_MAX){
		/* dx = 0 */
		slopeAC = 0;
	}else if(slopeAC == -DBL_MAX){
		/* dy = 0 */
		return;	
	}
	if( (slopeAB = getSlope(a,b)) == DBL_MAX){
		/* dx = 0 */
		slopeAB = 0;
	}else if(slopeAB == -DBL_MAX){
		/* dy = 0 */
		return;
	}
	
	while(1){
		y = (int)round(stPt.y);
		for(int i = (int)round(stPt.x); i <= (int)round(endPt.x); i++){
			checkBnd(&y, &i);
			screenBuff[y][i] = ascii;
		}
		if( vectorIsEqual(stPt, b)) break;
		stPt.x += slopeAB;
		stPt.y += 1.0;
		endPt.x += slopeAC;
		endPt.y += 1.0;
	}	
}
/* Function checks if coordinate is inside screen buffer boundrys */
void checkBnd(int *y, int *x){
	if( *x >= col ){
		*x = col - 1;
	}else if( *x < 0 ){
		*x = 0;
	}

	if( *y >= row ){
		*y = row - 1;
	}else if( *y < 0 ){
		*y = 0;
	}
}

void checkVectorBnd(struct vector *pt){
	if( pt->x >= col ){
		pt->x = col - 1;
	}else if(pt->x < 0){
		pt->x = 0;
	}

	if( pt->y >= row ){
		pt->y = row - 1;
	}else if( pt->y < 0 ){
		pt->y = 0;
	}
}

/* Returns the slope between the vectors. 
 * -> double_max if x-val is constant
 *struct  -> double_min if y-val is constant
 * -> double val for everything else
 */
double getSlope(struct vector a, struct vector b){
	double dx, dy;
	dx = b.x - a.x;
	if(dx == 0) return DBL_MAX;
	dy = b.y - a.y;
	if(dy == 0) return -DBL_MAX;
	return dx / dy;
}
/* Return the vector closest to the x-axis closest to the y-axis */
struct vector nearX(struct vector a, struct vector b){
	if(a.y < b.y) return a;
	if(a.y == b.y){
		return (a.x < b.x) ? a : b; 
	}
	return b;
}

bool vectorIsEqual(struct vector a, struct vector b){
	const double epsilon = 1e-6;
	return fabs(a.x-b.x) < epsilon && fabs(a.y-b.y) < epsilon;
}

/* Debug method */
void clearBuf(int row, int col){
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++)
			screenBuff[r][c] = ' ';
}

const char* face_colors[] = {
    "\033[91m",  //Red
    "\033[32m",  //Green
    "\033[33m",  //Yellow
    "\033[34m",  //Blue
    "\033[35m",  //Magenta
    "\033[36m",  //cosYan
    NULL, 
};

void printCube(int row, int col, bool colorIsSet){

	int r, c, n, bufSize, colorSize;
	colorSize = (int)(sizeof(face_colors) / sizeof(face_colors[0]));
	bufSize = col * (colorSize + 1);
	char linebuf[bufSize + 1];
	const char *colorStr, *reset_color = "\033[0m";
	CUP(1,1);

	for(r = 0; r < row; r++){
		if(colorIsSet){
			char *pStr = linebuf;
			size_t remaining = sizeof(linebuf);
			for(c = 0; c < col; c++){
				colorStr = getColor(screenBuff[r][c]);
				n = snprintf(pStr, remaining, "%s%c", (colorStr) ? colorStr : reset_color, screenBuff[r][c]);
				if( n < 0 || (size_t)n >= remaining) break;
				/* Increment pointer to buffer */
				pStr += n;
				/* Adjust remaining size */
				remaining -= n;
				if(!colorStr) *pStr = '\0';

			}
				/* Write buffer to screen */
				fwrite(linebuf, 1, (size_t)(pStr - linebuf), stdout);
		}else{
			fwrite(screenBuff[r], 1, col, stdout);
		}
	/* Go to next row */
	CNL();
	}
}

const char* getColor(char ch){
	int index;
	switch(ch){
		case '#': index = 0; break; 
		case 'o': index = 1; break;
		case '=': index = 2; break;
		case '*': index = 3; break;
		case '%': index = 4; break;
		case '$': index = 5; break;
		default: index = 6;
	}
	return face_colors[index];
}

/* 
 * Dot product between a vector and direction if viewer
 */
double dotProd(struct vector v1, struct vector v2){
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

struct vector crossProd(struct vector a, struct vector b){
	struct vector prod;
	prod.x = a.y*b.z - a.z*b.y;
	prod.y = a.z*b.x - a.x*b.z;
	prod.z = a.x*b.y - a.y*b.x;
	return prod;
}

/* Returns the resulting vector between point v1 and v2 */
struct vector calcVec(struct vector v1, struct vector v2){
	struct vector temp = {round(v2.x - v1.x), round(v2.y - v1.y), round(v2.z - v1.z)};
	return temp;
}

void scalePt(struct vector *pt, double scale){
	pt->x *= scale;
	pt->y *= scale;
}

/* Moves pt to fit screen */
void movePt(struct vector *pt, int row, int col){ 
	/* Scale x-coordinate by factor of col/row for correct resolution */
	double aspect_ratio = (double)col / (double)row;
	pt->x = round(pt->x * aspect_ratio +  ((double)col / 2));
	pt->y = round(pt->y + ((double)row / 2));
}

void projPt(struct vector *pt){
	double fl = 1.0;
	if(pt->z > 0){
		/* Focal lenght, projection plane at f = z */
		pt->x = (pt->x * fl) / pt->z;
		pt->y = (pt->y * fl) / pt->z;
	}else{
		printf("[projPt] ERROR! z = %f x = %f y = %f\n", pt->z, pt->x, pt->y);	
	}
}
void printInfo(void){
	printf("Display a 3D ascii cube\n");
	printf("### How to use program ###\n");
	printf("Run the program including 3 input arguments in the following order:\n");
	printf(" 1: [int] Row -> How many rows the window displaying the cube has\n");
	printf(" 2: [int] Col -> How many coloumns the windows displaying the cube has. NOTE: The value of Col should be double that of Row, i.e Col = 2*Row\n");
	printf(" 3: [int] Scale -> How big the cube is\n");
	printf(" 4: [Optional] To enable face colors use the flag -c or -color\n");
	printf("To exit the program type either 'q' or 'clear' in the termainal running the program\n");
}		
/* Convert ascii to integer */
int _atoi(char *str){
	int val = 0, sign = 1, indx = 0;
	if(str == NULL) return -1;
	if(str[0] == '-'){
		sign = -1;
		indx++;
	}
	while(str[indx] != '\0')
		val = 10 * val + (str[indx++] - '0');
	return sign * val;
}

/* If user input CTRL+D, reset cursor and color scheme */
void handle_sigint(int signal){
	CURSHW();
	COLOR_RESET();
	exit(0);
}

