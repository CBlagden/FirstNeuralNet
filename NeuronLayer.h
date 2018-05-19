#ifndef _NEURONLAYER_H_
#define _NEURONLAYER_H_

#include "LinAlgUtil.h"
#include "Neuron.h"

namespace nnet
{

	typedef lin_alg::Matrix Matrix;
	typedef unsigned int uint;

	class NeuronLayer
	{
	private:
		Matrix weights;
		Neuron neuron;

	public:
		NeuronLayer();
		NeuronLayer(uint inputLength, uint neuronsLength, NeuronType neuronType);
		NeuronLayer(Matrix &weights, NeuronType neuronType);
		void write(std::string filename) const;
		void read(std::string filename);
		Matrix getWeights();
		void setWeights(Matrix &weights);
		double getNeuronOutput(double x, bool deriv);
		NeuronType getNeuronType();
		void setNeuronType(NeuronType neuronType);
	};

} // namespace nnet

#endif