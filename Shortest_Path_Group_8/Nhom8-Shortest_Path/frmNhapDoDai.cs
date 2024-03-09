using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Nhom8_Shortest_Path
{
    public partial class frmNhapDoDai : Form
    {
        public frmNhapDoDai()
        {
            InitializeComponent();
        }
        public int Weight { get; set; }


        private void btnOK_Click(object sender, EventArgs e)
        {
            // Try to parse the textbox input as an integer
            bool success = int.TryParse(txtDoDai.Text, out int weight);

            // If the input is valid
            if (success && weight > 0)
            {
                // Set the weight property
                Weight = weight;

                // Close the form with OK result
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
            else
            {
                // Show an error message
                MessageBox.Show("Vui lòng nhập một số nguyên dương.", "Lỗi", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            // Close the form with Cancel result
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
