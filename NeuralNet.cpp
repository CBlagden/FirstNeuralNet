#include "NeuralNet.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <math.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

namespace nnet
{

	void NeuralNetwork::train(Matrix &input, Matrix &output, double learningRate)
	{
		if (input.size() != output.size())
		{
			std::cerr << "Input size " << input.size() << " must equal output size " << output.size() << "\n";
			return;
		}
		else if (neuronLayers.size() < 1) {
			std::cerr << "must add neuronLayer to function" << "\n";
			return;
		}

		outputError = output - run(input);
		Matrix error = outputError;

		Matrix delta;
		for (int i = neuronLayers.size() - 1; i > -1; i--)
		{
			std::function<double(double)> func =
				[&](double x) {
				return neuronLayers[i].getNeuronOutput(x, true);
			};
			Matrix z = run(input, i);
			Matrix weights = neuronLayers[i].getWeights();
			Matrix delta = error.hadamardProduct(z.transform(func));
			error = delta * weights.transpose();
			Matrix new_weights = weights + (z.transpose() * delta) * learningRate;
			neuronLayers[i].setWeights(new_weights);
		}

	}

	Matrix NeuralNetwork::run(Matrix &input, uint layers)
	{
		Matrix output = input;
		NeuronLayer neuronLayer = neuronLayers[0];
		std::function<double(double)> func = [&](double x) {
			return neuronLayer.getNeuronOutput(x, false);
		};
		for (int i = 0; i < layers; i++)
		{
			neuronLayer = neuronLayers[i];
			output = output * neuronLayer.getWeights();
			output = output.transform(func);
		}
		return output;
	}

	void NeuralNetwork::write(std::string filename)
	{
		if (CreateDirectory(filename.c_str(), NULL))
		{
			std::cout << "Creating directory " << filename << "\n";
		}
		else if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			std::cout << filename << " already exists"
				<< "\n";
		}
		else
		{
			std::cerr << "Could not write to " << filename << "\n";
			return;
		}
		for (int i = 0; i < neuronLayers.size(); i++)
		{
			neuronLayers[i].write(filename + "/layer" + std::to_string(i));
		}
	}

	void NeuralNetwork::read(std::string filename)
	{
		boost::filesystem::path p(filename);

		if (boost::filesystem::is_directory(p)) {
			if (neuronLayers.size() > 0)
			{
				neuronLayers.clear();
			}
			for (auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {})) 
			{
				std::string pathName = entry.path().string();
				Matrix weights = Matrix::read(pathName);
				NeuronType neuronType = Neuron::fromString(pathName.substr(pathName.find_last_of("_") + 1));
				NeuronLayer neuronLayer(weights, neuronType);
				neuronLayers.push_back(neuronLayer);
			}
		}

	}

	double NeuralNetwork::getError() const
	{
		return outputError.getAbs().getAverage();
	}

	void NeuralNetwork::clear()
	{
		neuronLayers.clear();
	}

	Matrix NeuralNetwork::run(Matrix &input)
	{
		return run(input, neuronLayers.size());
	}

	void NeuralNetwork::addLayer(uint inputLength, uint neuronsLength, NeuronType neuronType)
	{
		neuronLayers.emplace_back(inputLength, neuronsLength, neuronType);
	}

} // namespace nnet
