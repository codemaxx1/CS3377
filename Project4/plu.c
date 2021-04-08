//plu.c
#define n 8

double a[n][n];// = data matrix A
double l[n][n];// = lower: initialized to all 0 except L[i][i] = 1.0
for(int i = 0; a[i] != NULL; i++)
{
    a[i][i] = 1.0;
}

double u[n][n];// = upper: initilaized to all 0
int     p[n];//   = permutation vector; initialized as [0,1,2,,,.N-1]

// these are defined as row vectors but used as COLUMN vectors in the equations
double b[n];//   = constants vector;
double y[n];//   = temporary solution vector; initialied to 0
double x[n];//   = solution  vector

//                            Algorithm
// ================================================================
/*
int i, j, k;

for k = 0 to n-1 do{
max = 0;
for i = k to n-1 do {
if max < |a(i,k)| {
max = |a(i,k)|;
j = i;
}
if max == 0
error (singular matrix)

swap p[k] and p[j]             // exchanged row numbers
swap row a(k) and row a(j)
swap l(k,0:k-2) and l(j,0:k-2)

u(k,k) = a(k,k)
for i = k+1 to n-1 do {
l(i,k) = a(i,k)/u(k,k)
u(k,i) = a(k,i)
}

for i = k+1 to n-1 do {
for j = k+1 to n-1 do {
a(i,j) = a(i,j) - l(i,k)*u(k,j)
}
}
}

// After getting P, L and U, solve L*Y = P*B; then U*X = Y;
// ============================================================================