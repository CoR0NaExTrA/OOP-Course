namespace TriangleApp;

class Program
{
    static int Main( string[] args )
    {
        try
        {
            if ( args.Length != 3 )
            {
                Console.WriteLine( "неизвестная-ошибка" );
                return 1;
            }

            if ( !double.TryParse( args[ 0 ], out double a ) ||
                !double.TryParse( args[ 1 ], out double b ) ||
                !double.TryParse( args[ 2 ], out double c ) )
            {
                Console.WriteLine( "неизвестная-ошибка" );
                return 1;
            }

            Console.WriteLine( GetTriangleType( a, b, c ) );
            return 0;
        }
        catch
        {
            Console.WriteLine( "неизвестная-ошибка" );
            return 1;
        }
    }

    static string GetTriangleType( double a, double b, double c )
    {
        if ( a <= 0 || b <= 0 || c <= 0 )
            return "не-треугольник";

        if ( a + b <= c || a + c <= b || b + c <= a )
            return "не-треугольник";

        if ( a == b && b == c )
            return "равносторонний";

        if ( a == b || a == c || b == c )
            return "равнобедренный";

        return "обычный";
    }
}
