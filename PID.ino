// (Really Simple) PID Class by Ivan Seidel
// GitHub.com/ivanseidel
// Use as you want. Leave credits

class PID{
public:
	
	double error;
	double sample;
	double lastSample;
	double kP, kI, kD;      
	double P, I, D;
	double pid;
	
	double setPoint;
	long lastProcess;
	
	PID(double _kP, double _kI, double _kD){
		kP = _kP;
		kI = _kI;
		kD = _kD;
	}
	
	void addNewSample(double _sample){
		sample = _sample;
	}
	
	void setSetPoint(double _setPoint){
		setPoint = _setPoint;
	}
	
	double process(){
		// Implementação P ID
		error = setPoint - sample;
		float deltaTime = (millis() - lastProcess) / 1000.0;
		lastProcess = millis();
		
		//P
		P = error * kP;
		
		//I
		I = I + (error * kI) * deltaTime;
		
		//D
		D = (lastSample - sample) * kD / deltaTime;
		lastSample = sample;
		
		// Soma tudo
		pid = P + I + D;
		
		return pid;
	}
};
