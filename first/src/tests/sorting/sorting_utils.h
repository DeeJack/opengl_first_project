#pragma once
#include <mutex>
#include <vector>

#include "../../util.h"

#include "irrKlang/irrKlang.h"

static void on_finish(std::vector<SortingElement>& elements)
{
	for (int i = 0; i != elements.size(); ++i)
	{
		elements[i].object->set_color(normalize_color(255, 0, 0));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	for (int i = 0; i != elements.size(); ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		elements[i].object->set_color(normalize_color(255, 255, 255));
	}
}

static void swap(std::vector<SortingElement>& elements, int i, int j)
{

}

static void bubble_sort(std::vector<SortingElement>& elements, std::mutex& shapes_mutex, bool& ready, int& comparisons)
{
	for (int i = 0; i != elements.size(); ++i)
	{
		elements[i].object->set_color(normalize_color(254, 101, 0));
		for (int j = i + 1; j != elements.size(); ++j)
		{
			elements[j].object->set_color(normalize_color(102, 255, 51));
			comparisons++;
			if (elements[i].value > elements[j].value)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
				elements[j].object->set_color(normalize_color(255, 255, 255));
				shapes_mutex.lock();
				ready = true;
				auto temp2 = elements[i];
				elements[i] = elements[j];
				elements[j] = temp2;
				elements[i].object->set_color(normalize_color(255, 255, 255));
				shapes_mutex.unlock();
			}
			else
				elements[j].object->set_color(normalize_color(255, 255, 255));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		elements[i].object->set_color(normalize_color(255, 255, 255));
	}
	on_finish(elements);
}

static void insertion_sort(std::vector<SortingElement>& elements, std::mutex& shapes_mutex, bool& ready, int& comparisons)
{
	static irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
	for (int i = 1; i != elements.size(); ++i)
	{
		SortingElement key = elements[i];
		elements[i].object->set_color(normalize_color(102, 255, 51));
		std::cout << "Selecting element " << i << ": " << key.value << std::endl;
		int j = i - 1;
		comparisons++;
		while (j >= 0 && elements[j].value > key.value)
		{
			SoundEngine->play2D("res/bip.wav");
			comparisons++;
			std::cout << "\tSwitching with element " << j << ": " << elements[j].value << std::endl;
			elements[j + 1].object->set_color(normalize_color(0, 255, 0));
			elements[j].object->set_color(normalize_color(0, 0, 255));

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			shapes_mutex.lock();

			ready = true;
			elements[j + 1].object->set_color(normalize_color(255, 255, 255));
			elements[j].object->set_color(normalize_color(255, 255, 255));

			elements[j + 1] = elements[j];
			shapes_mutex.unlock();

			--j;
		}

		shapes_mutex.lock();

		ready = true;
		elements[j + 1] = key;
		shapes_mutex.unlock();
		std::cout << "\nCurrent situation: ";

		for (const auto& x : elements)
		{
			std::cout << x.value << ", ";
		}
		std::cout << "\n";
		elements[i].object->set_color(normalize_color(255, 255, 255));
	}
	on_finish(elements);
}
