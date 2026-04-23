using System.Diagnostics;

namespace TriangleTester;

class Program
{
    static void Main( string[] args )
    {
        if ( args.Length != 3 )
        {
            Console.WriteLine( "Использование:" );
            Console.WriteLine( "TriangleTester.exe <tests.txt> <triangle.exe> <result.txt>" );
            return;
        }

        string testFile = args[ 0 ];
        string triangleExe = args[ 1 ];
        string resultFile = args[ 2 ];

        var results = new string[ File.ReadAllLines( testFile ).Length ];
        int index = 0;

        foreach ( var line in File.ReadAllLines( testFile ) )
        {
            if ( string.IsNullOrWhiteSpace( line ) )
                continue;

            var parts = line.Split( ' ', StringSplitOptions.RemoveEmptyEntries );
            if ( parts.Length < 4 )
            {
                results[ index++ ] = "error";
                continue;
            }

            string expected = parts[ 3 ].Trim().ToLower();
            string actual = RunTriangle( triangleExe, parts[ 0 ], parts[ 1 ], parts[ 2 ] );

            results[ index++ ] = actual == expected ? "success" : "error";
        }

        File.WriteAllLines( resultFile, results );
    }

    static string RunTriangle( string exePath, string a, string b, string c )
    {
        try
        {
            var process = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = exePath,
                    Arguments = $"{a} {b} {c}",
                    RedirectStandardOutput = true,
                    UseShellExecute = false,
                    CreateNoWindow = true
                }
            };

            process.Start();
            string output = process.StandardOutput.ReadLine();
            process.WaitForExit();

            return output?.Trim().ToLower() ?? "";
        }
        catch
        {
            return "";
        }
    }
}
