#ifndef SERIES_HH
#define SERIES_HH

class Series{

public:
    // Constructor
    Series(){
        this->current_index = 1;
        this->current_value = 0.;
    };

    // Destructor
    ~Series() {};

protected:
    unsigned int current_index;
    double current_value;

public:
    virtual double compute(unsigned int N) = 0;
    virtual double getAnalyticPrediction();
};

#endif