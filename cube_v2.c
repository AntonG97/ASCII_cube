#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>
#include <sys/select.h>

/* Moves the cursor to row x, col y */
#define CUP(x,y) printf("%c[%d;%dH",'\033', x,y);
/* Erase in display.
         x=0: Clear from cursor to end of screen
         x=1: Clear from cursor to beginning of screen 
         x=2: Clear entire screen and delete lines in scrollback buffer
*/
#define ED(x) printf("%c[%dJ",'\033', x);

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
int createScreenBuf(int, int);
void printScreen(int,int, bool);
void fillScreen(int , int );
const char* getColor(char);

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
char getASCII(int face);
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
int _atoi(char*);


int main(int argc, char **argv){
	if(!strcmp(*(argv + 1), "-h") || !strcmp(*(argv + 1), "-help")){
		printf("Display a 3D ascii cube\n");
		printf("### How to use program ###\n");
		printf("Run the program including 3 input arguments in the following order:\n");
		printf(" 1: [int] Row -> How many rows the window displaying the cube has\n");
		printf(" 2: [int] Col -> How many coloumns the windows displaying the cube has. NOTE: The value of Col should be double that of Row, i.e Col = 2*Row\n");
		printf(" 3: [int] Scale -> How big the cube is\n");
		printf(" 4: [Optional] To enable face colors use the flag -c or -color\n");
		printf("To exit the program type either 'q' or 'clear' in the termainal running the program\n");
		return 0;
	}

	if(argc < 4){
		printf("How to start program: <Progam> <Screen width> <Screen height> <Cube size> [Optional] -color\n");
		return -1;
	}

	double distance = 3.5, scale = 20.0;
	struct vector cam ={0,0,1}, cross, v1, v2; 
	int size;
	char buffer[64];
	bool colorSet = false;

	row = _atoi(*(argv + 1));
	col = _atoi(*(argv + 2));
	scale = _atoi(*(argv + 3));

	if(argc == 5)
		if(!strcmp(*(argv+4), "-color") || !strcmp(*(argv+4), "-c"))
			colorSet = true;

	if(createScreenBuf(row, col) != 0){
		printf("Allocation of screen buffer failed!\n");
		return -1;
	}
	fillScreen(row, col);
	/* Set alternate screen to isolate program */
	printf("\033[?1049h");
	while(1){
		//CUP(1,1);
		//ED(2);

		printf("\033[2J\033[H");
		fillScreen(row, col);
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
		printScreen(row,col, colorSet);

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

		int r = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
		if (r > 0 && FD_ISSET(STDIN_FILENO, &fds)) {
			if (fgets(buffer, sizeof(buffer), stdin)) {
				/* Remove newline */
				buffer[strcspn(buffer, "\n")] = '\0';

				if (strcmp(buffer, "clear") == 0 || strcmp(buffer, "q") == 0) {
				break;
				}
			}
		}
		usleep(17500);
		fflush(stdin);
	}
	for(int r = 0; r < row; r++)
		free(*(screenBuff + r));
	free(screenBuff);
	
	/* Disable alternate screen */
	printf("\033[?1049l");
	return 0;
}

/* Allocates memory for screen buffer. Origo on [0,0] */
int createScreenBuf(int row, int col){
	int i;
	//int **tempMap;
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
	static double aX = 0.0, aY = 0.0, aZ = 0.0;
	int i;
	double combR[3][3];
	double cx = cos(aX), sx = sin(aX);
	double cy = cos(aY), sy = sin(aY);
	double cz = cos(aZ), sz = sin(aZ);
	
	combR[0][0] = cz*cy;
	combR[0][1] = cz*sy*sx-sz*cx;
	combR[0][2] = cz*sy*cx +sz*sx;

	combR[1][0] = sz*cy;
	combR[1][1] = sz*sy*sx+cz*cx;
	combR[1][2] = sz*sy*cx-cz*sx;

	combR[2][0] = -sy;
	combR[2][1] = cy*sx;
	combR[2][2] = cy*cx;
	/* Rotate each vertice */
	for(i = 0; i < (int)(sizeof(cube) / sizeof(cube[0])); i++){
		v = cube[i];
		cube_rotated[i].x = combR[0][0]*v.x+combR[0][1]*v.y+combR[0][2]*v.z;
		cube_rotated[i].y = combR[1][0]*v.x+combR[1][1]*v.y+combR[1][2]*v.z;
		cube_rotated[i].z = combR[2][0]*v.x+combR[2][1]*v.y+combR[2][2]*v.z;
	}
	/* Float modulus */
	aX = fmod(aX + 0.01, 2*M_PI);
	aY = fmod(aY + 0.02, 2*M_PI);
	aZ = fmod(aZ + 0.03, 2*M_PI);
}

char getASCII(int face){
	switch(face){
		case 0: return '#';
		case 1: return 'o';
		case 2: return '=';
		case 3: return '*';
		case 4: return '#';
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
	
	//FlatTop
	if(v0.y == v1.y){
		drawFlatTop(v0,v1,v2,ascii);
		return;
	}else if(v1.y == v2.y){
		//Flat bot
		drawFlatBot(v0,v1,v2, ascii);
		return;
	}
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
		//stPt.x = fabs(stPt.x + slopeAC);
		stPt.x += slopeAC;
		stPt.y += 1.0;
		//endPt.x = fabs(endPt.x + slopeBC);
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
		//dx = 0
		slopeAC = 0;
	}else if(slopeAC == -DBL_MAX){
		//dy
		return;	
	}
	if( (slopeAB = getSlope(a,b)) == DBL_MAX){
		//dx = 0
		slopeAB = 0;
	}else if(slopeAB == -DBL_MAX){
		//dy = 0
		return;
	}
	
	while(1){
		y = (int)round(stPt.y);
		for(int i = (int)round(stPt.x); i <= (int)round(endPt.x); i++){
			checkBnd(&y, &i);
			screenBuff[y][i] = ascii;
		}
		if( vectorIsEqual(stPt, b)) break;
		//stPt.x = fabs(stPt.x + slopeAB);
		stPt.x += slopeAB;
		stPt.y += 1.0;
		//endPt.x = fabs(endPt.x + slopeAC);
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
		//struct vector temp = nearY(a,b);
		return (a.x < b.x) ? a : b; 
	}
	return b;
}

bool vectorIsEqual(struct vector a, struct vector b){
	const double epsilon = 1e-6;
	return fabs(a.x-b.x) < epsilon && fabs(a.y-b.y) < epsilon;
}

/* Debug method */
void fillScreen(int row, int col){
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++)
			screenBuff[r][c] = ' ';
}

const char* face_colors[] = {
    "\033[31m",  //Red
    "\033[32m",  //Green
    "\033[33m",  //Yellow
    "\033[34m",  //Blue
    "\033[35m",  //Magenta
    "\033[36m",  //Cyan
    "\033[0m",  //Reset 
};

void printScreen(int row, int col, bool colorSet){
	for(int r = 0; r < row; r++){
		for(int c = 0; c < col; c++)
			if(colorSet){
				printf("%s%c\033[0m", getColor(screenBuff[r][c]),screenBuff[r][c]);
			}else{
				printf("%c", screenBuff[r][c]);
			}
		printf("\n");
	}
}

const char* getColor(char ch){
	int index;
	switch(ch){
		case '#': index = 0; break; 
		case 'o': index = 1; break;
		case '=': index = 2; break;
		case '*': index = 3; break;
		//case '#': index = 4; break;
		case '$': index = 5; break;
		default: index = 6;
	}
	return face_colors[index];
}

/* 
 * Dot product between a vector and direction if viewer
 */
double dotProd(struct vector v1, struct vector v2){
	//Paralell = 1
	//Perpendicular = 0
	//Pararell but reversed = -1
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

