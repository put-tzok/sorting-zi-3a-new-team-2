#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 1000, 2000,3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, };

void fill_increasing(int *t, unsigned int n) {
    // TODO: implement
    for (int i = 0; i <= n - 1; i++) {
                t[i] = i;
            }
}

void fill_decreasing(int *t, unsigned int n) {
    // TODO: implement
    for (int i = 0; i <= n - 1; i++) {
                t[i] = n - i - 1;
            }
}

void fill_vshape(int *t, unsigned int n) {
    int v;
    v = n / 2;
    for(int i = 0; i < v; i++)
    {
        t[i] = (v - i) * 2;
    }
    for(int i = v; i < n; i++)
    {
        t[i] = (i - v) * 2 + 1;
    }
}

void selection_sort(int *t, unsigned int n) {
    // TODO: implement
    for (int i = 0; i < n - 1; i++)
	{
		int najm = najmniejszy(t, i, n);


		int t2 = t[i];
		t[i] = t[najm];
		t[najm] = t2;
	}
}
int najmniejszy(int *t, int start, int n)
{
	int i = start;
	for (int j = start + 1; j < n; j++)
	{
		if (t[j] < t[i])
		{
			i = j;
		}
	}
	return i;
}

void insertion_sort(int *t, unsigned int n) {
    int key, i;
    for(int j = 1; j < n; j++)
    {
        key = t[j];
        i = j;
        while(i > 0 && t[i-1] > key)
        {
            t[i] = t[i-1];
            i--;
        }
        t[i] = key;
    }
}

void swap(int *t, int i, int j)
{
    int tmp = t[i];
    t[i] = t[j];
    t[j] = tmp;
}
int partition(int *t, int p, int r)
{
    int x, i;
    x = t[r];
    i = p - 1;
    for(int j = p; j <= r - 1; j++)
    {
        if(t[j] < x)
        {
            i = i + 1;
            swap(t, i, j);
        }
    }
    i = i + 1;
    swap(t, i, r);
    return i;
}



void quick_sort1(int *t, int low, int high)
{
    int pi;
    if (low < high)
    {
        pi = partition(t, low, high);
        quick_sort1(t, low, pi - 1);
        quick_sort1(t, pi + 1, high);
    }
}
void quick_sort(int *t, unsigned int n) {
    // TODO: implement
    quick_sort1(t,0, n-1);
}



void heap_sort(int *t, unsigned int n) {
    // TODO
    for (int i = n / 2; i >= 0; i--)
		funkcja_heap(t, n, i);

	for (int i = n - 1; i > 0; i--)
	{

		int t3 = t[0];
		t[0] = t[i];
		t[i] = t3;

		funkcja_heap(t, i, 0);
	}
}
void funkcja_heap(int *t, int n, int rodzic)
{
	int lewy = rodzic * 2 + 1;
	int prawy = lewy + 1;


	if (lewy < n && t[lewy] > t[rodzic])
	{

		int t2 = t[rodzic];
		t[rodzic] = t[lewy];
		t[lewy] = t2;

		funkcja_heap(t, n, lewy);
	}

	if (prawy < n && t[prawy] > t[rodzic])
	{
		int t2 = t[rodzic];
		t[rodzic] = t[prawy];
		t[prawy] = t2;


		funkcja_heap(t, n, prawy);
	}
}
void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
