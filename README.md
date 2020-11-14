# Jail

Just another interpreted language.

### CSharp

``` CSharp
using System;
using System.Text;
using System.Runtime.InteropServices;

namespace InterOp
{

    class Program 
    {

        #region DllImports

        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Jail();
        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void setVar([MarshalAs(UnmanagedType.LPStr)] string name, [MarshalAs(UnmanagedType.LPStr)] string type, [MarshalAs(UnmanagedType.LPStr)] string value);
        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getInt([MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double getDouble([MarshalAs(UnmanagedType.LPStr)] string name);
        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern void getString(string name, StringBuilder buffer, int len);
        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void interpretCode([MarshalAs(UnmanagedType.LPStr)] string code);
        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void interpret();
        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int Foo(StringBuilder buffer, int capacity);
        [DllImport("jail.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void setIndex(int index);

        #endregion

        static void Main(string[] args)
        {

            int interpreter = Jail();

            setVar("a", "string", "Hello, world");
            setVar("b", "int", "1984");
            setVar("c", "double", "3.14159");

            string code = "a += '!'; b = b * 2; c += 0.345;";
            interpretCode(code);

            StringBuilder a = new StringBuilder(128);
            getString("a", a, a.Capacity);
            int b = getInt("b");
            double c = getDouble("c");

            Console.WriteLine("a = " + a + ", b = " + b + ", c = " + c);

        }

    }
}

```

### C++
``` Cpp

// define exported functions
__declspec(dllimport) int Jail();    
__declspec(dllimport) void setIndex(int index);    
__declspec(dllimport) void setVar(char *name, char *type, char *value);    
__declspec(dllimport) int getInt(char *name);    
__declspec(dllimport) double getDouble(char *name);    
__declspec(dllimport) void getString(char *name, char *buffer, int n);    
__declspec(dllimport) char* getObject(char *name);    
__declspec(dllimport) void interpretCode(char *code);    
__declspec(dllimport) void interpret();

int main() {
    
    int interpreter = Jail();
    
    setVar("a", "string", "Hello, world");
    setVar("b", "int", "1984");
    setVar("c", "double", "3.14159");  
    
    const char *code = "a += '!'; b = b * 2; c += 0.345;";      
    interpretCode(strdup(code));
    delete [] code;
            
    char *a = (char *)malloc(128); //new char[128];
    getString("a", a, 128); 
    int b = getInt("b");
    double c = getDouble("c"); 
    printf("%s %d %f", a, b, c);          
    return 0;
    
}

````
