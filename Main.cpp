#include "LinAlgUtil.h"
#include "NeuralNet.h"
#include <iostream>
#include <time.h>
#include <ratio>
#include <chrono>

typedef std::vector<std::vector<double>> mat;

static void testNeuralNet()
{
	mat mat_input({ { 0, 0 },{ 0, 1 },{ 1, 0 },{ 1, 1 } });
	lin_alg::Matrix input(mat_input);

	mat mat_output({ { 0 },{ 1 },{ 1 },{ 0 } });
	lin_alg::Matrix output(mat_output);

	nnet::NeuralNetwork nnet;
	
	std::cout << "Training..." << std::endl;
	nnet.addLayer(2, 9, nnet::NeuronType::SIGMOID);
	nnet.addLayer(9, 4, nnet::NeuronType::SIGMOID);
	nnet.addLayer(4, 1, nnet::NeuronType::SIGMOID);
	nnet.write("nnet");
	while (true) 
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < 10000; i++) {
			nnet.train(input, output, 0.4);
			if (i % 2000 == 0)
				std::cout << "Error: " << nnet.getError() << "\n";
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto diff = end - begin;
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
		std::cout << "Finished training in " << ms << " ms" << std::endl;
		std::cout << nnet.run(input).toString() << std::endl;
		if (nnet.getError() < 0.1)
			nnet.write("nnet");
		else 
		{
			nnet.clear();
			nnet.addLayer(2, 9, nnet::NeuronType::SIGMOID);
			nnet.addLayer(9, 4, nnet::NeuronType::SIGMOID);
			nnet.addLayer(4, 1, nnet::NeuronType::SIGMOID);
		}
			
	}
	
}

int main(int argc, char **argv)
{
	testNeuralNet();
	system("pause");
	return 0;
}
