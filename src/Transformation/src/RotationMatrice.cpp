#include "RotationMatrice.h"
#include "Angle.h"

double* RotationMatrice::operator[](std::size_t index)
{
	return m_[index];
}

const double* RotationMatrice::operator[](std::size_t index) const
{
    return m_[index];
}

void RotationMatrice::set(
    const Angle &x,
    const Angle &y,
    const Angle &z)
{
    m_[0][0] = z.cos() * y.cos();
    m_[0][1] = z.cos() * y.sin() * x.sin() - z.sin() * x.cos();
    m_[0][2] = z.cos() * y.sin() * x.cos() + z.sin() * x.sin();

    m_[1][0] = z.sin() * y.cos();
    m_[1][1] = z.sin() * y.sin() * x.sin() + z.cos() * x.cos();
    m_[1][2] = z.sin() * y.sin() * x.cos() - z.cos() * x.sin();

    m_[2][0] = -y.sin();
    m_[2][1] = y.cos() * x.sin();
    m_[2][2] = y.cos() * x.cos();
}