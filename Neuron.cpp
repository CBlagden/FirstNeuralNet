#include "Neuron.h"
#include <math.h>
#include <iostream>

namespace nnet
{

	inline double Neuron::sigmoid(double x)
	{
		double result = 1.0 / (1.0 + exp(-x));
		if (std::isnan(result))
		{
			return 0.0;
		}
		return result;
	}

	inline double Neuron::tanh(double x)
	{
		return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
	}

	inline double Neuron::getOutput(double x, NeuronType neuronType, bool deriv)
	{
		switch (neuronType)
		{
		case RELU:
			if (x > 0)
				return deriv ? 1 : x;
			else
				return 0;
		case SIGMOID:
			return deriv ? sigmoid(x) * (1 - sigmoid(x)) : sigmoid(x);
		case TANH:
			return deriv ? 1 - tanh(x) * tanh(x) : tanh(x);
		}
		return -1;
	}

	std::string Neuron::toString() const
	{
		switch (neuronType)
		{
		case SIGMOID:
			return "sigmoid";
		case RELU:
			return "relu";
		case TANH:
			return "tanh";
		}
	}

	NeuronType Neuron::fromString(std::string s) {
		if (s == "sigmoid") {
			return NeuronType::SIGMOID;
		}
		else if (s == "relu") {
			return NeuronType::RELU;
		}
		else if (s == "tanh") {
			return NeuronType::TANH;
		}
		return NeuronType::SIGMOID;
	}

	double Neuron::getOutput(double x, bool deriv)
	{
		return getOutput(x, neuronType, deriv);
	}

	void Neuron::setNeuronType(NeuronType neuronType)
	{
		this->neuronType = neuronType;
	}

	NeuronType Neuron::getNeuronType()
	{
		return neuronType;
	}

} // namespace nnet
