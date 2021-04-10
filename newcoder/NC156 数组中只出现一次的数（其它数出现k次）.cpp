#include <iostream>

int foundOnceNumber(int *arr, int length, int k)
{
	int *binarySum = new int[32];
	for (int i = 0; i < 32; i++)
	{
		int sum = 0;
		for (int j = 0; j < length; j++)
			sum += (arr[j] >> i) & 1;
		binarySum[i] = sum;
	}

	int res = 0;
	for (int i = 0; i < 32; i++)
	{
		if (binarySum[i] % k != 0)
			res += 1 << i;
	}
	return res;
}

int main(int argc, char *argv[])
{
	int arr[] = {5, 4, 4, 1, 5, 4, 5}, k = 3;
	std::cout << "array: ";
	for (auto &e : arr)
		std::cout << e << ' ';
	std::cout << "\nonce number: " << foundOnceNumber(arr, sizeof(arr) / sizeof(int), k) << std::endl;

	return 0;
}