using System;

namespace QuickCS
{
    class Program
    {
        static void Main(string[] args)
        {
            float[,] vertices;
            int circleDivis = 8;
            float thick = 0.975f;
            float angle = (float)((System.Math.PI * 2) / circleDivis);

            vertices = new float[3, circleDivis * 6];

            for(int i = 0; i < circleDivis; i++)
            {
                vertices[0, i * 6] = (float)Math.Cos(angle * i) * thick;
                vertices[1, i * 6] = (float)Math.Sin(angle * i) * thick;
                vertices[2, i * 6] = 0.0f;
                
                vertices[0, (i * 6) + 1] = (float)Math.Cos(angle * (i + 1));
                vertices[1, (i * 6) + 1] = (float)Math.Sin(angle * (i + 1));
                vertices[2, (i * 6) + 1] = 0.0f;

                vertices[0, (i * 6) + 2] = (float)Math.Cos(angle * i);
                vertices[1, (i * 6) + 2] = (float)Math.Sin(angle * i);
                vertices[2, (i * 6) + 2] = 0.0f;

                
                vertices[0, (i * 6) + 3] = (float)Math.Cos(angle * i) * thick;
                vertices[1, (i * 6) + 3] = (float)Math.Sin(angle * i) * thick;
                vertices[2, (i * 6) + 3] = 0.0f;
                

                vertices[0, (i * 6) + 4] = (float)Math.Cos(angle * (i + 1)) * thick;
                vertices[1, (i * 6) + 4] = (float)Math.Sin(angle * (i + 1)) * thick;
                vertices[2, (i * 6) + 4] = 0.0f;

                vertices[0, (i * 6) + 5] = (float)Math.Cos(angle * (i + 1));
                vertices[1, (i * 6) + 5] = (float)Math.Sin(angle * (i + 1));
                vertices[2, (i * 6) + 5] = 0.0f;
            }



            string result = "";
            for(int i = 0; i < circleDivis * 6; i++)
            {
                result +="{ " + vertices[0, i].ToString("0.00000000000f") + ", " +
                              vertices[1, i].ToString("0.00000000000f") + ", " +
                              vertices[2, i].ToString("0.00000000000f") + " },\n";
                Console.Write(result);
            }
            System.IO.File.WriteAllText("output.txt", result);
        }
    }
}
