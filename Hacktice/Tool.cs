using System;
using System.Windows.Forms;

namespace Hacktice
{
    public partial class Tool : Form
    {
        public Tool()
        {
            InitializeComponent();
        }

        private void buttonPatch_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                Filter = "ROMs (*.z64)|*.z64|All files (*.*)|*.*",
                FilterIndex = 1,
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    Patcher patcher = new Patcher(openFileDialog.FileName);
                    patcher.Apply();
                    MessageBox.Show("Patch applied successfully!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception)
                {
                    MessageBox.Show("Failed to patch!", "hacktice", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
        }

        private int FindHackticeConfigPosition(byte[] payload)
        {
            // The main payload has part that is constant and part that is in the end and has 'HCFG' magic in it
            // round to 4, most likely it is unnecessary but just in case
            int off = payload.Length - (payload.Length % 4) - 4;
            while (off != 0)
            {
                if (payload[off] == 'H' && payload[off + 1] == 'C' && payload[off + 2] == 'F' && payload[off + 3] == 'G')
                {
                    return off;
                }

                off -= 4;
            }

            throw new ArgumentException("Failed to find Hacktice config in the payload");
        }

        private void buttonGSCode_Click(object sender, EventArgs e)
        {
            GameSharkCodeGenerator generator;
            generator = new GameSharkCodeGenerator();

            XmlPatches patches = new XmlPatches();
            foreach (var patch in patches)
            {
                // Ignore code that copies from ROM to RAM
                if (patch.Offset == 0x396c || patch.Offset == 0x7f1200)
                    continue;

                generator.Add((uint)patch.Offset, patch.Data, 0, patch.Data.Length, true);
            }

            int hcfgOff = FindHackticeConfigPosition(Resource.data);
            generator.Add(0x7f2000, Resource.data, 0, hcfgOff, true);
            generator.Add(0x7f2000 + (uint) hcfgOff, Resource.data, hcfgOff, Resource.data.Length - hcfgOff, false);

            richTextBox1.Text = generator.Create();
        }
    }
}
