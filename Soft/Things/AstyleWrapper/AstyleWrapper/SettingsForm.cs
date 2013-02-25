using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AstyleWrapper
{
    public partial class SettingsForm : Form
    {
        AStyleInterface ai;

        public SettingsForm(AStyleInterface ai)
        {
            InitializeComponent();

            pgProps.SelectedObject = ai;
            this.ai = ai;
            tbCode.Text = ai.FormatSource(tbCode.Text);
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            ai.SaveSettings();
            DialogResult = DialogResult.OK;
            Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            AStyleInterface.LoadSettings(ref ai);
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void SettingsForm_Load(object sender, EventArgs e)
        {
            ai.SaveSettings();
        }

        private void btnDefaults_Click(object sender, EventArgs e)
        {
            ai.LoadDefaults();
            ai.SaveSettings();
            pgProps.Refresh();
            tbCode.Text = ai.FormatSource(tbCode.Text);
        }

        private void pgProps_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            tbCode.Text = ai.FormatSource(tbCode.Text);
        }
    }
}
