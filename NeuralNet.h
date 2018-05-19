/*
* NeuralNet.h
*
*  Created on: May 3, 2018
*      Author: CBlagden
*/

#ifndef NEURALNET_H_
#define NEURALNET_H_

#include "LinAlgUtil.h"
#include "NeuronLayer.h"
#include <vector>


namespace nnet
{

	typedef nnet::NeuronType NeuronType;
	typedef unsigned int uint;
	typedef lin_alg::Matrix Matrix;

	class NeuralNetwork
	{
	private:
		std::vector<NeuronLayer> neuronLayers;
		Matrix run(Matrix &input, uint layers);
		Matrix outputError;
	public:
		void train(Matrix &input, Matrix &output, double learningRate);
		Matrix run(Matrix &input);
		void addLayer(uint inputLength, uint neuronsLength, NeuronType neuronType);
		void write(std::string filename);
		void read(std::string filename);
		double getError() const;
		void clear();
	};

} // namespace nnet

#endif 
