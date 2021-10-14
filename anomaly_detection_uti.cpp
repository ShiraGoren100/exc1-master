//**********************
//* Name:Roi Avraham
//* Id: 318778081
//*with:
//Name: Shira Goren
//Id: 207814989
//**********************
#include <iostream>

//returns x average
float avg(float* x, int size) {
    float sum;
    float m;
    for(int i=0; i<size; i++) {
        sum += (x[i]);
    }
    m = (1/size) * sum;
    return m;
}

// returns the variance of X and Y
float var(float* x, int size){
    //initialize variables for sums and return value
    float squaredSum = 0;
    float expectedValue = 0;
    float inverseSize = (float (1) / float (size));
    float varReturn = 0;

    /*
     * this loop adds all floats from x
     * to create a sum and a squared sum.
     * */
    for(int i = 0; i < size; i++) {
        expectedValue += *x;
        squaredSum += pow(*x, 2);
        x++;
    }
    expectedValue = pow((inverseSize * expectedValue), 2);
    varReturn = (inverseSize * squaredSum) - expectedValue;
    return varReturn;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float ex = avg(x, size);
    float ey = avg(y, size);
    float sum = 0;
    for(int i=0; i<size; i++) {
        sum += ((x[i] - ex) * (y[i] - ey));
    }
    float covariance = sum * (1/size);
    return covariance;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    float covariance = cov(x, y, size);
    float sigmaX = sqrt(double(var(x, size)));
    float sigmaY = sqrt(double(var(y, size)));
    float p = covariance / (sigmaX * sigmaY);
    return p;
}

// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size) {
    float* x;
    float* y;
    float a;
    float b;
    for(int i = 0;i< size; i++) {
        x[i] = points[i]->getX();
        y[i] = points[i]->getY();
    }
    a = cov(x, y, size) / var(x, size);
    float aveX = E(x,size);
    float aveY = E(y, size);
    b = aveY - (a * aveX);
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size) {
    Line line = linear_reg(points, size);
    float f = line.f(p.getX());
    float deviation = abs(f - p.getY());
    return deviation;
}

// returns the deviation between point p and the line
float dev(Point p,Line l) {
    float f = l.f(p.getX());
    float deviation = abs(f - p.getY());
    return deviation;
}
