string[] arr = System.IO.File.ReadAllLines("input.txt");

int globalSum = 0;
int localSum = 0;

foreach (var item in arr)
{
    if (string.IsNullOrEmpty(item)) {
        if (localSum > globalSum) {
            globalSum = localSum;
        }
        localSum = 0;
    } else {
        int res = 0;
        Int32.TryParse(item, out res);
        localSum = localSum + res;
    }
    System.Console.WriteLine("Result {0}", globalSum);

}

