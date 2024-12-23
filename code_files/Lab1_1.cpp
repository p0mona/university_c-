

//Task1
#include <iostream>
#include <cmath>

double degreesToRadiansValue(double degrees)
{
    return degrees * (M_PI / 180.0);
}

void degreesToReference(double &degrees)
{
    degrees = degrees * (M_PI / 180.0);
}

void degreesToPointer(double *degrees)
{
     if (degrees != nullptr) {
        *degrees = (*degrees) * M_PI / 180.0;
    }
}

//Tests
int main(){
    double angleOfATriangle_1 = 50.0;
    double angleOfATriangle_2 = 30.0;
    double angleOfATriangle_3 = 60.0;

    double angleOfATriangleInRadians_1 = degreesToRadiansValue(angleOfATriangle_1);
    std::cout << "The angle " << angleOfATriangle_1 << " is passed by value and is " << angleOfATriangleInRadians_1 << " radians." << std::endl;

    double angleOfATriangleInRadians_2 = angleOfATriangle_2;
    degreesToReference(angleOfATriangle_2);
    std::cout << "The angle " << angleOfATriangleInRadians_2 << " when passed by reference is " << angleOfATriangle_2 << " radians." << std::endl;

    double angleOfATriangleInRadians_3 = angleOfATriangle_3;
    degreesToPointer(&angleOfATriangle_3);
    std::cout << "The angle " << angleOfATriangleInRadians_3 << " when passed through a pointer is " << angleOfATriangle_3 << " radians." << std::endl;

    return 0;
}
