#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>

#include <benchmark/benchmark.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_STDIO
#include "stb_image.h"

constexpr const char* FILE_NAME = "../aya.jpg";

static void BM_File_Stdio(benchmark::State& state) {
	for (auto _ : state) {
		FILE* file = fopen(FILE_NAME, "r");

		fseek(file, 0, SEEK_END);
		const size_t fileSize = ftell(file);
		rewind(file);

		unsigned char* buffer = (unsigned char*)malloc(fileSize);
		fread(buffer, 1, fileSize, file);

		fclose(file);

		int width, height, channels;
		unsigned char* image = stbi_load_from_memory(buffer, fileSize, &width, &height,
				&channels, 4);

		stbi_image_free(image);

		free(buffer);
	}
}

static void BM_File_Windows(benchmark::State& state) {
	for (auto _ : state) {
		HANDLE file = CreateFileA(FILE_NAME, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		DWORD fileSize = GetFileSize(file, NULL);

		unsigned char* buffer = (unsigned char*)malloc(fileSize);
		ReadFile(file, buffer, fileSize, NULL, NULL);

		CloseHandle(file);

		int width, height, channels;
		unsigned char* image = stbi_load_from_memory(buffer, fileSize, &width, &height,
				&channels, 4);

		stbi_image_free(image);

		free(buffer);
	}
}

static void BM_File_MemoryMap(benchmark::State& state) {
	for (auto _ : state) {
		HANDLE file = CreateFileA(FILE_NAME, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		HANDLE fileView = CreateFileMappingA(file, NULL, PAGE_READONLY, 0, 0, NULL);
		void* memory = MapViewOfFile(fileView, FILE_MAP_READ, 0, 0, 0);
		size_t fileSize = GetFileSize(file, NULL);

		unsigned char* buffer = reinterpret_cast<unsigned char*>(memory);

		int width, height, channels;
		unsigned char* image = stbi_load_from_memory(buffer, fileSize, &width, &height,
				&channels, 4);

		stbi_image_free(image);

		UnmapViewOfFile(memory);
		CloseHandle(fileView);
		CloseHandle(file);
	}
}

BENCHMARK(BM_File_Stdio);
BENCHMARK(BM_File_Windows);
BENCHMARK(BM_File_MemoryMap);

BENCHMARK_MAIN();

