const int inf = 2000000000; 
const int mxn = 1e5 + 5;
int n, a[mxn], L[mxn], I[mxn]; 

int LisNlogK() { 
    int i; 
    I[0] = -inf; 
    for( i = 1; i <= n; i++ ) I[i] = inf; 
    int LisLength = 0; 
    for( i = 0; i < n; i++ ) { 
        int low, high, mid; 
        low = 0; 
        high = LisLength; 
        while( low <= high ) { 
            mid = ( low + high ) / 2;
            if( I[mid] < a[i] ) low = mid + 1;
            else                       high = mid - 1;
        }
        
        I[low] = a[i];
        if( LisLength < low ) LisLength = low;
    }
    return LisLength; 
}
