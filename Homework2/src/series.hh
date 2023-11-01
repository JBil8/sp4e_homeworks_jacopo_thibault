#ifndef SERIES_HH
#define SERIES_HH

class Series {
public:
    // Constructor for the Series class, initializes the current_index and current_value
    Series() {
        this->current_index = 1;
        this->current_value = 0.0;
    }

    // Destructor for Series (empty implementation as no additional cleanup is needed)
    ~Series() {};

protected:
    unsigned int current_index; // Current index of the series
    double current_value;       // Current value of the series

public:
    // Pure virtual function for computing the series up to the specified number of iterations (N)
    virtual double compute(unsigned int N) = 0;

    // Virtual function to get the analytic prediction (can be overridden in derived classes)
    virtual double getAnalyticPrediction();
};

#endif
