using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using Microsoft.Xna.Framework;


namespace prevadec
{
    public partial class Form1 : Form
    {

        char[] x = new char[500];
        char[] x1 = new char[500];
        char[] cut = new char[500];
        char[] rollc = new char[500];
        int[] ad = new int[10];
        Quaternion quat,quat1, quat2, quat_out;
        int i = 0;
        string rolls;
        private SerialPort port = new SerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
        private SerialPort port2 = new SerialPort("COM1", 115200, Parity.None, 8, StopBits.One);

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.port.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            if (!port.IsOpen)
            {
                port.Open();
            }
            else
            {
                port.Close();
            }
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //this.port2.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort2_DataReceived);
            if (!port2.IsOpen)
            {
                port2.Open();
            }
            else
            {
                port2.Close();
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
           
            while (port.BytesToRead > 0)
            {
                
                    port.Read(x, i, 1);     
                    if (x[i] == '\r')
                    {
                        zobraz();
                        i = 0;
                    }
                    i++;
                    if (i > 499)
                    {
                        i = 0;
                    }
            }

        }

        private void serialPort2_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {

  
        }


        private void zobraz()
        {
            int ad_num,quat_num, j;            
            string q, s = new string(x);
            long del = 16384;

            for (ad_num = 1; ad_num < 11; ad_num++) //vyber postupně všechny data ad převodníků z řetězce
            {
                q = "ad" + ad_num + ":";            //formát dat v řetězci

                if (s.Contains(q))
                {
                    int i = s.IndexOf(q) + q.Length; //do paměti následující znak obsahující první číslici
                    j = i;


                    while (x[i] != '\t' && x[i] != '\r' && (i - j) < 100) //vyber znaky ke speciálnímu znaku
                    {
                        rollc[i - j] = x[i];                      //ulož do char[] pole
                        i++;
                    }


                    rolls = string.Join("", rollc);                 //převeď char[] pole na string

                    try
                    {
                        ad[ad_num - 1] = (int)Convert.ToDouble(rolls);  //konverze stringu obsahujícího číslice na číslo int
                    }
                    catch (FormatException)                         //vyjímka převodu
                    {
                        System.Console.WriteLine("Unable to convert '{0}' to a Int.", rolls);
                    }
                    Array.Clear(rollc, 0, rollc.Length);
                }
            }

            for (quat_num = 1; quat_num < 13; quat_num++)
            {
                q = "quat" + quat_num + ":";
                if (s.Contains(q))
                {
                    int i = s.IndexOf(q) + q.Length;
                    j = i;

                    while (x[i] != '\t' && x[i] != '\r' && (i - j) < 100)
                    {
                        rollc[i - j] = x[i];
                        i++;
                    }
                    q = rollc[0].ToString();

                    rolls = string.Join("", rollc);

                    try
                    {
                        switch (quat_num)
                        {
                            case 1:
                                quat1.W = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 2:
                                quat1.Z = -(float)Convert.ToDouble(rolls) / del;
                                break;
                            case 3:
                                quat1.X = -(float)Convert.ToDouble(rolls) / del;
                                break;
                            case 4:
                                quat1.Y = (float)Convert.ToDouble(rolls) / del;
                                break;

                            case 5:
                                quat.W = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 6:
                                quat.Z = -(float)Convert.ToDouble(rolls) / del;
                                break;
                            case 7:
                                quat.X = -(float)Convert.ToDouble(rolls) / del;
                                break;
                            case 8:
                                quat.Y = (float)Convert.ToDouble(rolls) / del;
                                break;

                            case 9:
                                quat2.W = (float)Convert.ToDouble(rolls) / del;
                                break;
                            case 10:
                                quat2.Z = -(float)Convert.ToDouble(rolls) / del;
                                break;
                            case 11:
                                quat2.X = -(float)Convert.ToDouble(rolls) / del;
                                break;
                            case 12:
                                quat2.Y = (float)Convert.ToDouble(rolls) / del;
                                break;

                            default: break;
                        }
                    }
                    catch (FormatException)
                    {
                        Console.WriteLine("Unable to convert '{0}' to a Double.", rolls);
                    }
                    Array.Clear(rollc, 0, rollc.Length);
                }

            }

            
        }


        public static Vector3 FromQ2(Quaternion q1)
        {
            float sqw = q1.W * q1.W;
            float sqx = q1.X * q1.X;
            float sqy = q1.Y * q1.Y;
            float sqz = q1.Z * q1.Z;
            float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
            float test = q1.X * q1.W - q1.Y * q1.Z;
            Vector3 v;

            if (test > 0.4995f * unit)
            { // singularity at north pole
                v.Y = MathHelper.ToDegrees(2f * (float)Math.Atan2(q1.Y, q1.X));
                v.X = MathHelper.ToDegrees((float)Math.PI / 2);
                v.Z = 0;
                return NormalizeAngles(v);
            }
            if (test < -0.4995f * unit)
            { // singularity at south pole
                v.Y = MathHelper.ToDegrees(-2f * (float)Math.Atan2(q1.Y, q1.X));
                v.X = MathHelper.ToDegrees((float)-Math.PI / 2);
                v.Z = 0;
                return NormalizeAngles(v);
            }
            Quaternion q = new Quaternion(q1.W, q1.Z, q1.X, q1.Y);
            v.Y = MathHelper.ToDegrees((float)Math.Atan2(2f * q.X * q.W + 2f * q.Y * q.Z, 1 - 2f * (q.Z * q.Z + q.W * q.W)));     // Yaw
            v.X = MathHelper.ToDegrees((float)Math.Asin(2f * (q.X * q.Z - q.W * q.Y)));                                         // Pitch
            v.Z = MathHelper.ToDegrees((float)Math.Atan2(2f * q.X * q.Y + 2f * q.Z * q.W, 1 - 2f * (q.Y * q.Y + q.Z * q.Z)));      // Roll
            return NormalizeAngles(v);
        }

        static Vector3 NormalizeAngles(Vector3 angles)
        {
            angles.X = NormalizeAngle(angles.X);
            angles.Y = NormalizeAngle(angles.Y);
            angles.Z = NormalizeAngle(angles.Z);
            return angles;
        }

        static float NormalizeAngle(float angle)
        {
            while (angle > 360)
                angle -= 360;
            while (angle < 0)
                angle += 360;
            return angle;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (port2.IsOpen)
            {
                pictureBox1.BackColor = System.Drawing.Color.SpringGreen;
            }
            else
            {
                pictureBox1.BackColor = System.Drawing.Color.Red;
            }
            if (port.IsOpen)
            {
                pictureBox2.BackColor = System.Drawing.Color.SpringGreen;
            }
            else
            {
                pictureBox2.BackColor = System.Drawing.Color.Red;
            }

            int pom;
            char[] ch = new char[8];
            int[] serv = new int[6];
            Vector3 eul;
            Quaternion qu = new Quaternion();
            qu.W = 1;
            qu.X = 0;
            qu.Y = -1;
            qu.Z = 0;
            qu.Normalize();

            serv[0] = (int)(ad[0] * 0.5 + ad[1] * 0.5);
            serv[1] = ad[2];
            serv[2] = ad[4];
            serv[3] = ad[6];
            serv[4] = ad[8];

            quat_out = Quaternion.Multiply(Quaternion.Conjugate(quat2), Quaternion.Multiply(quat1, qu)); //Quaternion.Multiply(Quaternion.Conjugate(quat2), quat1);

            eul = FromQ2(quat_out);
            if (eul.Z > 200)
            {
                serv[5] = (int)((eul.Z) / (double)0.990);
                if (serv[5] < 0)
                { serv[5] = 0; }
                if (serv[5] > 100)
                { serv[5] = 100; }
            }

            richTextBox5.Text = serv[0].ToString();
            richTextBox6.Text = serv[1].ToString();
            richTextBox7.Text = serv[2].ToString();
            richTextBox8.Text = serv[3].ToString();
            richTextBox9.Text = serv[4].ToString();
            richTextBox10.Text = serv[5].ToString();

            ch[0] = (char)101;
            for (pom = 1; pom < 7; pom++)
            {
                ch[pom] = Convert.ToChar(serv[(pom - 1)]);
            }
            ch[7] = (char)101;
            if (port2.IsOpen)
            {
                port2.Write(ch, 0, 8);
            }

            richTextBox1.Text = quat_out.W.ToString();
            richTextBox2.Text = quat_out.X.ToString();
            richTextBox3.Text = quat_out.Y.ToString();
            richTextBox4.Text = quat_out.Z.ToString();

            richTextBox11.Text = eul.Z.ToString();
            richTextBox12.Text = eul.Y.ToString();
            richTextBox13.Text = eul.X.ToString();
        }

    

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            port.Close();
            port2.Close();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }


    }
}
