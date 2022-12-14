#include <iostream>

using namespace std;

int get_max (int a[], int n){
   int max = a[0];
   for (int i = 1; i < n; i++)
      if (a[i] > max)
         max = a[i];
   return max;
}

void radix_sort (int a[], int n){
   int bucket[10][10], bucket_cnt[10];
   int i, j, k, r, NOP = 0, divisor = 1, lar, pass;
   lar = get_max (a, n);
   while (lar > 0){
      NOP++;
      lar /= 10;
   }
   for (pass = 0; pass < NOP; pass++){
      for (i = 0; i < 10; i++){
         bucket_cnt[i] = 0;
      }
      for (i = 0; i < n; i++){
         r = (a[i] / divisor) % 10;
         bucket[r][bucket_cnt[r]] = a[i];
         bucket_cnt[r] += 1;
      }
      i = 0;
      for (k = 0; k < 10; k++){
         for (j = 0; j < bucket_cnt[k]; j++){
            a[i] = bucket[k][j];
            i++;
         }
      }
      divisor *= 10;
      cout << "After pass: " << pass + 1;
      for (i = 0; i < n; i++)
         cout << a[i] << " ";
      cout << "\n";
   }
}
int main (){
   int i, n, a[10];
   cout << "Enter the number of items to be sorted: ";
   cin >> n;
   
   cout << "Enter items: ";
   for (i = 0; i < n; i++){
      cin >> a[i];
   }
   
   radix_sort (a, n);
   cout << "Sorted items : ";
   for (i = 0; i < n; i++)
     cout << a[i];
   cout << "\n";
   return 0;
}