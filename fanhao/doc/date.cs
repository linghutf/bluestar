using System;

namespace Test
{
    public class MainTest
    {
        public static void Main(string[] args)
        {
            /*
            DateTime d1 = DateTime.Today;
            DateTime d2 = new DateTime(2017,1,19);
            Console.WriteLine("{0}",d1.CompareTo(d2));
            string str = "2007-10-10";
            if(DateTime.TryParse(str,out d1))
            {
                Console.WriteLine("date:{0}",d1);
            }
            */
            if(args.Length!=1)
            {
                Console.WriteLine("Usage:exe 1991-01-01");
                return;
            }
            DateTime dt;
            if(DateTime.TryParse(args[0],out dt))
            {
                Console.WriteLine("{0}",UnixFromDateTime(dt));
            }

        }

        public static long UnixFromDateTime(DateTime dt)
        {
            DateTime dtStart = TimeZone.CurrentTimeZone.ToLocalTime(new DateTime(1970,1,1));
            TimeSpan ts = dt.Subtract(dtStart);
            return ts.Ticks/10000000;
        }

        public static DateTime DateTimeFromUnix(long d)
        {
            DateTime dtStart = TimeZone.CurrentTimeZone.ToLocalTime(new DateTime(1970,1,1));
            TimeSpan ts = new TimeSpan(d);
            DateTime dtResult = dtStart.Add(ts);
            return dtResult;
        }
    }
}
