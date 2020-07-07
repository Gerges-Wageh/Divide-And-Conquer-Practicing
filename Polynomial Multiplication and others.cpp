#include <iostream>

using namespace std;

int BinarySearch(int arr[], int l, int r, int key){

    if(l>r)
            return l;

    int m = (r+l)/2;
    if(key==arr[m])
        return m;

    else if(key>arr[m])
        return BinarySearch(arr,m+1,r,key);
    else
        return BinarySearch(arr,l,m-1,key);

}
void PolyMult(int a[], int b[], int n, int c[]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            c[i+j]+=a[i]*b[j];
        }
    }

}

int* PolyMultiNaive(int* A, int* B, int n, int a, int b){
    int* R = new int[2*n-1];
    for(int i=0;i<2*n-1;i++)R[i]=0;
    if(n==1){
        R[0]=A[a]*B[b];
        return R;
    }
    int* temp1= PolyMultiNaive(A,B,n/2,a,b);
    for(int i=0;i<n-1;i++){
        R[i]=temp1[i];
    }
    temp1= PolyMultiNaive(A,B,n/2,a+(n/2),b+(n/2));
    int j=0;
    for(int i=n;i<2*n-1;i++){
        R[i]=temp1[j++];
    }
    delete []temp1;
    j=0;
    temp1= PolyMultiNaive(A,B,n/2,a,b+(n/2));
    int* temp2= PolyMultiNaive(A,B,n/2,a+(n/2),b);
    for(int i=n/2;i<n+n/2-1;i++){
        R[i]+=temp1[j]+temp2[j];
        j++;
    }
    delete []temp1;
    delete []temp2;
    return R;

}
void S(int* arr, int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[i])
                swap(arr[i],arr[j]);
        }
    }
}

int* Merge(int* B, int* C , int B_l, int B_r, int C_l, int C_r){
    int s = (C_r-C_l)+(B_r-B_l)+2;
    int* D = new int [s];
    int k=0;
    while(C_l<=C_r&&B_l<=B_r){
        if(B[B_l]<=C[C_l]){
            D[k++]=B[B_l++];
        }
        else{
            D[k++]=C[C_l++];
        }
    }
    while(B_l<=B_r)
        D[k++]=B[B_l++];
    while(C_l<=C_r)
        D[k++]=C[C_l++];

    return D;
}

int* MergeSort(int* A, int l, int r){
    if(l>=r)
        return A;
    int m = (r+l)/2;
    int B[m-l+1];
    int C[r-m];
    for(int i=0;i<m-l+1;i++)B[i]=A[i];
    for(int i=0;i<r-m;i++)C[i]=A[i+m+1];
    for(int i=0;i<m-l+1;i++)cout<<B[i]<< " ";
    cout<<endl;
    for(int i=0;i<r-m;i++)cout<<C[i]<< " ";
    cout<<endl<<endl;
    int* x = MergeSort(B,0,m-l);
    int* y = MergeSort(C,0,r-m-1);
    int* D = Merge(x,y,0,m,0,r-m);
    return D;
}
//the previous 2 functions cause memory overhead so, we are going to enhance it

void Opt_Merge(int arr[], int l, int m, int r){
    int i=0,j=0,k=l;
    int s1=m-l+1;
    int s2=r-m;
    //temp arrays
    int left[s1], right[s2];
    //copy the elements to the temp arrays
    for(int i=0;i<s1;i++)left[i]=arr[l+i];
    for(int i=0;i<s2;i++)right[i]=arr[i+m+1];
    //merging step
    while(i<s1 && j<s2){
        if(left[i]<=right[j])
            arr[k++]=left[i++];
        else
            arr[k++]=right[j++];
    }

    //copying the rest of left array, if there are any.
    while(i<s1)
        arr[k++]=left[i++];

    //copying the rest of right, if there are any.
    while(j<s2)
        arr[k++]=right[j++];
}
void Opt_MergeSort(int arr[], int l, int r){

    if(l==r)  // base case when the array contains only 1 element
        return;

        int m = l+(r-l)/2;        //the same as (r+l)/2 but this is better to avoid integer overflow in case of large arrays
        Opt_MergeSort(arr,l,m);   //call the merge sort function for the first half
        Opt_MergeSort(arr,m+1,r); //call the merge sort function for the second half
        Opt_Merge(arr,l,m,r);     //merging the 2 halves
}
void SelectionSrot(int arr[], int n){
    int min_idx;
    for(int i=0;i<n-1;i++){
        min_idx = i;
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[min_idx])
                min_idx = j;
        }
        swap(arr[i],arr[min_idx]);
    }

}
int Partitioning(int A[], int l, int r){
    int temp[r-l+1];
    int left_idx=l, right_idx=r;
    for(int i=0;i<r-l+1;i++)temp[i]=A[i+l];
    for(int i=1;i<r-l+1;i++){
        if(temp[i]<=temp[l])
            A[left_idx++]=temp[i];
        else
            A[right_idx--]=temp[i];
    }
    A[right_idx]=temp[l];
    return right_idx;
}
int Partitioning_2(int A[], int l, int r){
    int j=l;
    for(int i=l+1;i<=r;i++){
        if(A[i]<A[l]){
            swap(A[j+1],A[i]);
            j++;
        }
    }
    swap(A[l],A[j]);
    return j;
}

void QuickSort(int A[], int l, int r){
    if(l>=r)
        return;
    int m = Partitioning_2(A,l,r);
    QuickSort(A,l,m-1);
    QuickSort(A,m+1,r);
}

int main()
{
    int A[]{1,2,5,2,1,9,2,2};
    QuickSort(A,0,7);
    for(int i=0;i<8;i++)cout<<A[i]<< " ";

    return 0;
}
