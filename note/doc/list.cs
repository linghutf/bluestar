using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SQLite;
using System.Data.SqlClient;
using System.Configuration; 

namespace HTML5SecurityScanner
{
    public partial class SetPoc : Form
    {
        private SQLiteConnection conn = null;
        private SQLiteDataAdapter da = null;
        SQLiteCommand command = null;
        DataSet ds = new DataSet();
        private const string sql_select = "select * from poc"; 
        public SetPoc()
        {
            InitializeComponent();
        }

        private void SetPoc_Load(object sender, EventArgs e)//查询
        {

            conn = new SQLiteConnection(ConfigurationSettings.AppSettings["connstr"]);
            conn.Open();
            command = new SQLiteCommand(sql_select,conn);
            da = new SQLiteDataAdapter(command);
            da.Fill(ds,"poc");
            this.PocDataGridView.DataSource = ds.Tables[0];
        }
        private void AltButton_Click(object sender, EventArgs e)//修改
        {
            SQLiteCommandBuilder scb = new SQLiteCommandBuilder(da);
            da.UpdateCommand = scb.GetUpdateCommand();
            da.Update(ds, "poc");
        }

        private void AddButton_Click(object sender, EventArgs e)//增加
        {
            SQLiteCommandBuilder scb = new SQLiteCommandBuilder(da);
            da.InsertCommand = scb.GetInsertCommand();
            da.Update(ds, "poc");
        }

        private void DelButton_Click(object sender, EventArgs e)//删除
        {
            ds.AcceptChanges();
            SQLiteCommandBuilder scb = new SQLiteCommandBuilder(da);
            ds.Tables[0].Rows[this.PocDataGridView.CurrentRow.Index].Delete();
            da.DeleteCommand = scb.GetDeleteCommand();
            da.Update(ds, "poc");
        }

        private void RefreshButton_Click(object sender, EventArgs e)//更新
        {
            this.conn = null;
            this.da = null;
            this.command = null;
            ds = new DataSet();
            conn = new SQLiteConnection(ConfigurationSettings.AppSettings["connstr"]);
            conn.Open();
            command = new SQLiteCommand(sql_select, conn);
            da = new SQLiteDataAdapter(command);
            da.Fill(ds, "poc");
            this.PocDataGridView.DataSource = ds.Tables[0];
            conn.Close();
        }
    }
}
