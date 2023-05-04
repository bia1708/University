namespace SpotifyApp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.aidDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.nameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.monthlylistenersDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.defaultfooDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.artistsBindingSource2 = new System.Windows.Forms.BindingSource(this.components);
            this.spotifyDataSetBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.spotifyDataSet = new SpotifyApp.SpotifyDataSet();
            this.artistsBindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.artistsBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.artistsTableAdapter = new SpotifyApp.SpotifyDataSetTableAdapters.ArtistsTableAdapter();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.alidDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.titleDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.aidDataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.albumsBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.albumsTableAdapter = new SpotifyApp.SpotifyDataSetTableAdapters.AlbumsTableAdapter();
            this.button1 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.artistsBindingSource2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spotifyDataSetBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.spotifyDataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.artistsBindingSource1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.artistsBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.albumsBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.AutoGenerateColumns = false;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.aidDataGridViewTextBoxColumn,
            this.nameDataGridViewTextBoxColumn,
            this.monthlylistenersDataGridViewTextBoxColumn,
            this.defaultfooDataGridViewTextBoxColumn});
            this.dataGridView1.DataSource = this.artistsBindingSource2;
            this.dataGridView1.Location = new System.Drawing.Point(0, 0);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 51;
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(554, 450);
            this.dataGridView1.TabIndex = 0;
            // 
            // aidDataGridViewTextBoxColumn
            // 
            this.aidDataGridViewTextBoxColumn.DataPropertyName = "aid";
            this.aidDataGridViewTextBoxColumn.HeaderText = "aid";
            this.aidDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.aidDataGridViewTextBoxColumn.Name = "aidDataGridViewTextBoxColumn";
            this.aidDataGridViewTextBoxColumn.Width = 125;
            // 
            // nameDataGridViewTextBoxColumn
            // 
            this.nameDataGridViewTextBoxColumn.DataPropertyName = "name";
            this.nameDataGridViewTextBoxColumn.HeaderText = "name";
            this.nameDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.nameDataGridViewTextBoxColumn.Name = "nameDataGridViewTextBoxColumn";
            this.nameDataGridViewTextBoxColumn.Width = 125;
            // 
            // monthlylistenersDataGridViewTextBoxColumn
            // 
            this.monthlylistenersDataGridViewTextBoxColumn.DataPropertyName = "monthly_listeners";
            this.monthlylistenersDataGridViewTextBoxColumn.HeaderText = "monthly_listeners";
            this.monthlylistenersDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.monthlylistenersDataGridViewTextBoxColumn.Name = "monthlylistenersDataGridViewTextBoxColumn";
            this.monthlylistenersDataGridViewTextBoxColumn.Width = 125;
            // 
            // defaultfooDataGridViewTextBoxColumn
            // 
            this.defaultfooDataGridViewTextBoxColumn.DataPropertyName = "default_foo";
            this.defaultfooDataGridViewTextBoxColumn.HeaderText = "default_foo";
            this.defaultfooDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.defaultfooDataGridViewTextBoxColumn.Name = "defaultfooDataGridViewTextBoxColumn";
            this.defaultfooDataGridViewTextBoxColumn.Width = 125;
            // 
            // artistsBindingSource2
            // 
            this.artistsBindingSource2.DataMember = "Artists";
            this.artistsBindingSource2.DataSource = this.spotifyDataSetBindingSource;
            // 
            // spotifyDataSetBindingSource
            // 
            this.spotifyDataSetBindingSource.DataSource = this.spotifyDataSet;
            this.spotifyDataSetBindingSource.Position = 0;
            // 
            // spotifyDataSet
            // 
            this.spotifyDataSet.DataSetName = "SpotifyDataSet";
            this.spotifyDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // artistsBindingSource1
            // 
            this.artistsBindingSource1.DataMember = "Artists";
            this.artistsBindingSource1.DataSource = this.spotifyDataSetBindingSource;
            // 
            // artistsBindingSource
            // 
            this.artistsBindingSource.DataMember = "Artists";
            this.artistsBindingSource.DataSource = this.spotifyDataSetBindingSource;
            // 
            // artistsTableAdapter
            // 
            this.artistsTableAdapter.ClearBeforeFill = true;
            // 
            // comboBox1
            // 
            this.comboBox1.DataSource = this.artistsBindingSource;
            this.comboBox1.DisplayMember = "name";
            this.comboBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(0, 0);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(800, 24);
            this.comboBox1.TabIndex = 1;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // dataGridView2
            // 
            this.dataGridView2.AutoGenerateColumns = false;
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.alidDataGridViewTextBoxColumn,
            this.titleDataGridViewTextBoxColumn,
            this.aidDataGridViewTextBoxColumn1});
            this.dataGridView2.DataSource = this.albumsBindingSource;
            this.dataGridView2.Location = new System.Drawing.Point(0, 24);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowHeadersWidth = 51;
            this.dataGridView2.RowTemplate.Height = 24;
            this.dataGridView2.Size = new System.Drawing.Size(554, 426);
            this.dataGridView2.TabIndex = 2;
            this.dataGridView2.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
            // 
            // alidDataGridViewTextBoxColumn
            // 
            this.alidDataGridViewTextBoxColumn.DataPropertyName = "alid";
            this.alidDataGridViewTextBoxColumn.HeaderText = "alid";
            this.alidDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.alidDataGridViewTextBoxColumn.Name = "alidDataGridViewTextBoxColumn";
            this.alidDataGridViewTextBoxColumn.Width = 125;
            // 
            // titleDataGridViewTextBoxColumn
            // 
            this.titleDataGridViewTextBoxColumn.DataPropertyName = "title";
            this.titleDataGridViewTextBoxColumn.HeaderText = "title";
            this.titleDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.titleDataGridViewTextBoxColumn.Name = "titleDataGridViewTextBoxColumn";
            this.titleDataGridViewTextBoxColumn.Width = 125;
            // 
            // aidDataGridViewTextBoxColumn1
            // 
            this.aidDataGridViewTextBoxColumn1.DataPropertyName = "aid";
            this.aidDataGridViewTextBoxColumn1.HeaderText = "aid";
            this.aidDataGridViewTextBoxColumn1.MinimumWidth = 6;
            this.aidDataGridViewTextBoxColumn1.Name = "aidDataGridViewTextBoxColumn1";
            this.aidDataGridViewTextBoxColumn1.Width = 125;
            // 
            // albumsBindingSource
            // 
            this.albumsBindingSource.DataMember = "Albums";
            this.albumsBindingSource.DataSource = this.spotifyDataSetBindingSource;
            // 
            // albumsTableAdapter
            // 
            this.albumsTableAdapter.ClearBeforeFill = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(609, 176);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "Add";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(609, 148);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(179, 22);
            this.textBox1.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(606, 119);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(85, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "Album name:";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(609, 216);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 6;
            this.button2.Text = "Delete";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(609, 259);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 7;
            this.button3.Text = "Update";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.artistsBindingSource2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spotifyDataSetBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.spotifyDataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.artistsBindingSource1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.artistsBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.albumsBindingSource)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.BindingSource spotifyDataSetBindingSource;
        private SpotifyDataSet spotifyDataSet;
        private System.Windows.Forms.BindingSource artistsBindingSource;
        private SpotifyDataSetTableAdapters.ArtistsTableAdapter artistsTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn aidDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn nameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn monthlylistenersDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn defaultfooDataGridViewTextBoxColumn;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.BindingSource artistsBindingSource1;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.BindingSource albumsBindingSource;
        private SpotifyDataSetTableAdapters.AlbumsTableAdapter albumsTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn alidDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn titleDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn aidDataGridViewTextBoxColumn1;
        private System.Windows.Forms.BindingSource artistsBindingSource2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
    }
}

