// Analog values for calibration
const float loadA = 16.99; // Lower bound weight g
const int analogvalA = 117; // analog reading taken with load A on the load cell
const float loadB = 1113.45; // Upper bound weight g
const int analogvalB = 1016; // analog reading taken with load B on the load cell
const double dens1 = 1.00; // Saline density @ 22C g/mL
/*

const double loadA = 71.45; // Lower bound weight g
const int analogvalA = 74.75; // analog reading taken with load A on the load cell
const double loadB = 1113.45; // Upper bound weight g
const int analogvalB = 19571.30; // analog reading taken with load B on the load cell
*/
double dataCollect(int ni) {
  double n = ni*1.0;
  
  
  double x[ni];
  double y[ni];
  double analogValue;
  double mll;
  double y0;
  double x0;
  int index;
  int ssd;

  
  for(index = 0; index < ni; index++) {
    
    ssd = analogRead(A8);
    
    analogValue = analogToLoad(ssd*1.0)/dens1; //get volume 
    Serial.print("analog: ");Serial.println(analogValue);
    mll=millis()/1000;
    //delay(300);
    if (index == 1) {
      y0 = analogValue;
      x0 = mll;
    }
    x[index] = mll - x0;
    y[index] = y0 - analogValue;
    
  }

  //double x[16] = {0, 0.1000, 0.2000, 0.3000, 0.4000, 0.5000, 0.6000, 0.7000, 0.8000, 0.9000, 1.0000, 1.1000, 1.2000, 1.3000, 1.4000, 1.5000};
  //double y[16] = {-0.0241, 0.3319, 0.6313, 0.8135, 1.1970, 1.4835, 1.8628, 2.2093, 2.5109, 2.6136, 3.0077, 3.1786, 5.4886, 3.8993, 4.3533, 4.4230};

  double m = simpleLinearRegression(x,y,ni);
  
  Serial.print("original m: "); Serial.print(m*3600);
  
  
  double theta = atan(m);
  double yo[ni];
  
  for(index = 0; index < ni; index++) {
    yo[index] = abs(-1*x[index]*sin(theta) + y[index]*cos(theta));
  }
  
  int CNT = noOut(x, y, yo, ni, m);
  
  double xi[CNT];
  double yi[CNT];
  
  filterFlat(x, y, yo, xi, yi, ni, m);
  
  double m2 = simpleLinearRegression(xi,yi,CNT);
  Serial.print(" new m: "); Serial.println(m2*3600);
  return abs(m2*3600);
  
  
  //arrayAdd2(x,y,yo,ni);
}


int filterFlat(double *x, double *y, double *yo, double *xi, double *yi, int n, double m) {
  double stdo = standard_deviation(yo,n)*sqrt(1 + m*m);
  //Serial.print("std: "); Serial.println(stdo);
  int CNT = 0;
  
  for(int index = 0; index < n; index++) {
    if (yo[index]<2*stdo) {
      xi[CNT] = x[index];
      yi[CNT] = y[index];
      ++ CNT;
      
    }
    else {
     //Serial.print("excluded: "); Serial.print(index);
    //Serial.print("number: "); Serial.println(yo[index]); 
    }
  }
  return CNT;
}

int noOut(double *x, double *y, double *yo, int n, double m) {
  double stdo = standard_deviation(yo,n)*sqrt(1 + m*m);
  int CNT = 0;
  
  for(int index = 0; index < n; index++) {
    if (yo[index]<2*stdo) {
      ++ CNT;
    }
  }
  return CNT;
}

double simpleLinearRegression(double *x, double *y, int ni) {
  double n = ni*1.0;
  
  double xy[ni];
  double x2[ni];
  
  double sx = arrayAdd(x,ni);
  double sy = arrayAdd(y,ni);
  
  arrayMult(x,y,xy,ni);
  arrayMult(x,x,x2,ni);
  
  double sxy = arrayAdd(xy,ni);
  double sx2 = arrayAdd(x2,ni);
  
  double m;

  
  m = (sxy - (1/n)*(sx)*(sy))/(sx2 - (1/n)*sx*sx);
  
  return m;
  
}

double arrayAdd(double *vec, int n) {

  int index;
  double total=0;

  for(index = 0; index < n; index++)
  {
    total += vec[index];
  }

  return(total); 

}

void arrayMult(double *vec1, double *vec2, double *vec3, int n) {

  int index;

  for(index = 0; index < n; index++)
  {
    vec3[index] = vec1[index]*vec2[index];
  }
  

}

void arrayAdd2(double *vec1, double *vec2, double *vec3, int n) {
  int index;

  for(index = 0; index < n; index++)
  {
    vec3[index] = vec1[index] + vec2[index];
  }
  

}

double standard_deviation(double data[], int n)
{
    double mean=0.0, sum_deviation=0.0;
    int i;
    
    for(i=0; i<n;++i)
    {
        mean+=data[i];
    }
    mean=mean/n;
    
    for(i=0; i<n;++i) {
    sum_deviation+=(data[i]-mean)*(data[i]-mean);
    }
    return sqrt(sum_deviation/(n-1));           
}

double analogToLoad(double analogval) {
  // using a custom map-function, because the standard arduino map function only uses int
  double load = mapdouble(analogval, analogvalA, analogvalB, loadA, loadB);
  return load;
}

double mapdouble(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
