﻿using System;
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
                    var rom = File.ReadAllBytes(args[0]);
                    Patcher patcher = new Patcher(rom);
                    if (!patcher.IsBinary())
                    {
                        MessageBox.Show("Only binary ROMs are supported!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                    }
                    patcher.Apply();
                    patcher.Save(args[0]);
                }
                catch (Exception)
                {
                    MessageBox.Show("Failed to apply patch!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
    }
}
