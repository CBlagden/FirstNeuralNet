#ifndef _NEURON_H_
#define _NEURON_H_

#include <string>

namespace nnet
{

	enum NeuronType
	{
		RELU,
		SIGMOID,
		TANH
	};

	class Neuron
	{
	private:
		NeuronType neuronType;
		double sigmoid(double x);
		double tanh(double x);
		double getOutput(double x, NeuronType neuronType, bool deriv);

	public:
		double getOutput(double x, bool deriv);
		void setNeuronType(NeuronType neuronType);
		NeuronType getNeuronType();
		std::string toString() const;
		static NeuronType fromString(std::string s);
	};

} // namespace nnet

#endif