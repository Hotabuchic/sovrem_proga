#include <clocale>
#include <iostream>

void calculate_prefix_sum(int pref_sum[], int arr[], const int arr_size, const int k);
void input_array(int arr[], const int n);
void print_array(const wchar_t* const comment, const int* const arr, const int n);
int* process_results(const int* const pref_sum, int q, const int k);

int main() {
    std::setlocale(LC_ALL, "Russian");

    int arr_size;
    std::wcout << L"Введите размер массива: ";
    std::cin >> arr_size;

    int* arr = new int[arr_size];
    input_array(arr, arr_size);

    int k;
    std::wcout << L"Введите ограничение массива сверху: ";
    std::cin >> k;

    int* pref_sum = new int[k];
    calculate_prefix_sum(pref_sum, arr, arr_size, k);

    int q;
    std::wcout << L"Введите кол-во запросов: ";
    std::cin >> q;

    int* result = process_results(pref_sum, q, k);
    print_array(L"Резуьтат запроса №", result, q);

    delete[] arr;
    delete[] pref_sum;
    delete[] result;

    return 0;
}

void calculate_prefix_sum(int pref_sum[], int arr[], const int arr_size, const int k) {
    for (int i = 0; i < k; i++) {
        pref_sum[i] = 0;
    }

    for (int i = 0; i < arr_size; i++) {
        pref_sum[arr[i]] += 1;
    }

    for (int i = 1; i < k; i++) {
        pref_sum[i] += pref_sum[i - 1];
    }
}

void input_array(int arr[], const int n) {
    std::wcout << L"Введите элементы массива через пробел (только целые не меньшие нуля числа): ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
}

void print_array(const wchar_t* const comment, const int* const arr, const int arr_size) {
    const char space = ' ';
    for (int i = 0; i < arr_size; i++) {
        std::wcout << comment << i + 1 << ":" << space << arr[i] << std::endl;
    }
}

int* process_results(const int* const pref_sum, int q, const int k) {
    int max_index;
    int min_index;
    int l;
    int r;

    const int result_size = q;
    int* result = new int[result_size];

    for (; q > 0; q--) {
        std::wcout << L"Введите нижнюю и верхнюю границы поиска (через пробел): ";
        std::cin >> l >> r;
        max_index = std::min(k - 1, r);
        min_index = std::max(0, l);
        if (min_index > 0) {
            result[result_size - q] = pref_sum[max_index] - pref_sum[min_index - 1];
        }
        else {
            result[result_size - q] = pref_sum[max_index];
        }
    }

    return result;
}
