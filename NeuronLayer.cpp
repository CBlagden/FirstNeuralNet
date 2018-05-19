#include <iostream>
#include "NeuronLayer.h"

namespace nnet
{

	NeuronLayer::NeuronLayer() {}

	NeuronLayer::NeuronLayer(uint inputLength, uint neuronsLength,
		NeuronType neuronType)
	{
		weights = lin_alg::Matrix::random(inputLength, neuronsLength);
		neuron.setNeuronType(neuronType);
	}

	NeuronLayer::NeuronLayer(Matrix & weights, NeuronType neuronType)
	{
		this->weights = weights;
		neuron.setNeuronType(neuronType);
	}


	void NeuronLayer::write(std::string filename) const
	{
		weights.write(filename + "_weights_" + neuron.toString());
	}

	void NeuronLayer::read(std::string filename)
	{
		weights = Matrix::read(filename);
		std::string neuronString = filename.substr(filename.rfind("_") + 1);
		neuron.setNeuronType(Neuron::fromString(neuronString));
	}

	Matrix NeuronLayer::getWeights()
	{
		return weights;
	}

	void NeuronLayer::setWeights(Matrix &weights)
	{
		this->weights = weights;
	}

	double NeuronLayer::getNeuronOutput(double x, bool deriv)
	{
		return neuron.getOutput(x, deriv);
	}

	NeuronType NeuronLayer::getNeuronType()
	{
		return	neuron.getNeuronType();
	}

	void NeuronLayer::setNeuronType(NeuronType neuronType)
	{
		neuron.setNeuronType(neuronType);
	}

}