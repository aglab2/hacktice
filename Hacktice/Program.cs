using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Xml;
using System.Windows.Forms;

namespace Hacktice
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Application.EnableVisualStyles();
                Application.Run(new Tool());
                return;
            }
            else
            {
                try
                {
                    Patcher patcher = new Patcher(args[0]);
                    patcher.Apply();
                }
                catch (Exception)
                {
                    MessageBox.Show("Failed to apply patch!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
    }
}
