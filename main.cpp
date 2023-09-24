#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class StockPricePredictor {
public:
  StockPricePredictor() {}

  void Train(const vector<double> &prices) {
    for (int i = 0; i < prices.size() - 1; i++) {
      x.push_back(prices[i]);
      y.push_back(prices[i + 1]);
    }

    double w = LeastSquares(x, y);
  }

  double Predict(double price) { return w[0] + w[1] * price; }

private:
  vector<double> x;
  vector<double> y;
  vector<double> w;

  double LeastSquares(const vector<double> &x, const vector<double> &y) {
    double sum_x = 0;
    double sum_y = 0;
    double sum_xx = 0;
    double sum_xy = 0;

    for (int i = 0; i < x.size(); i++) {
      sum_x += x[i];
      sum_y += y[i];
      sum_xx += x[i] * x[i];
      sum_xy += x[i] * y[i];
    }

    double b = (sum_xy - sum_x * sum_y / x.size()) /
               (sum_xx - sum_x * sum_x / x.size());
    double a = sum_y / x.size() - b * sum_x / x.size();

    return {a, b};
  }
};

int main() {
  StockPricePredictor predictor;

  vector<double> prices = {100, 105, 110, 115, 120};
  predictor.Train(prices);

  double price = 125;
  double prediction = predictor.Predict(price);

  cout << "The predicted price of the stock is " << setprecision(2)
       << prediction << endl;

  return 0;
}
