using System;
using System.Drawing;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Windows.Forms;
public class CustomForm : Form
{
   private const int WM_NCLBUTTONDOWN = 0xA1;
   private const int HT_CAPTION = 0x2;

   [DllImportAttribute("user32.dll")]
   private static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
   [DllImportAttribute("user32.dll")]
   private static extern bool ReleaseCapture();
   private Rectangle barRect;

   public CustomForm()
   {
      this.Paint += this.OnPaint;
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
      this.BackColor = Color.FromArgb(45, 45, 48);
      this.ForeColor = Color.FromArgb(241, 241, 241);
      this.MouseDown += this.OnMouseDown;
      this.Icon = Icon.ExtractAssociatedIcon(Assembly.GetExecutingAssembly().Location);
   }

   private void OnMouseDown(object sender, System.Windows.Forms.MouseEventArgs e)
   {
      if (e.Button == MouseButtons.Left && barRect.Contains(e.Location))
      {
         ReleaseCapture();
         SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
      }
   }

   private void InitializeComponent()
   {
            this.SuspendLayout();
            // 
            // CustomForm
            // 
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Name = "CustomForm";
            this.Load += new System.EventHandler(this.CustomForm_Load);
            this.ResumeLayout(false);

   }

   private void OnPaint(object sender, PaintEventArgs e)
   {
      this.Text = "Cyber Protector";
      barRect = new Rectangle(1, 1, this.Width - 2, 31);
      e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(37, 37, 38)), barRect);
      e.Graphics.DrawRectangle(new Pen(Color.FromArgb(63, 63, 70), 1), new Rectangle(1, 1, this.Width - 3, this.Height - 3));
      StringFormat sf = new StringFormat();
      sf.LineAlignment = StringAlignment.Near;
      sf.Alignment = StringAlignment.Near;
      e.Graphics.DrawString(this.Text, new Font(this.Font, FontStyle.Bold), new SolidBrush(Color.FromArgb(241, 241, 241)), new Rectangle(30, 10, this.Width - 3, this.Height - 3), sf);
      e.Graphics.DrawIcon(Builder.Properties.Resources.speed, new Rectangle(10, 10, 16, 16));
   }

    private void CustomForm_Load(object sender, EventArgs e)
    {

    }
}

public class CustomButton : Button
{
   private bool hover = false;
   public CustomButton()
   {
      this.Paint += this.OnPaint;
      this.MouseLeave += this.OnMouseLeave;
      this.MouseEnter += this.OnMouseEnter;
   }
   private void OnMouseEnter(object sender, EventArgs e)
   {
      hover = true;
   }
   private void OnMouseLeave(object sender, EventArgs e)
   {
      hover = false;
   }
   private void OnPaint(object sender, PaintEventArgs e)
   {
      e.Graphics.FillRectangle(new SolidBrush((hover ? Color.FromArgb(44, 44, 48) : Color.FromArgb(33, 33, 34))), new Rectangle(0, 0, this.Width, this.Height));
      e.Graphics.DrawRectangle(new Pen((hover ? Color.FromArgb(70, 70, 70) : Color.FromArgb(60, 60, 60)), 1), new Rectangle(0, 0, this.Width - 1, this.Height - 1));
      StringFormat sf = new StringFormat();
      sf.LineAlignment = StringAlignment.Center;
      sf.Alignment = StringAlignment.Center;
      e.Graphics.DrawString(this.Text, this.Font, new SolidBrush(Color.FromArgb(241, 241, 241)), new Rectangle(0, 0, this.Width, this.Height), sf);
   }
}

public class TopCustomButton : Button
{
   private bool hover = false;
   public TopCustomButton()
   {
      this.Paint += this.OnPaint;
      this.MouseLeave += this.OnMouseLeave;
      this.MouseEnter += this.OnMouseEnter;
   }
   private void OnMouseEnter(object sender, EventArgs e)
   {
      hover = true;
   }

   private void OnMouseLeave(object sender, EventArgs e)
   {
      hover = false;
   }

   private void OnPaint(object sender, PaintEventArgs e)
   {
      Color hoverColor = Color.FromArgb(37, 37, 38);
      if (hover)
      {
         hoverColor = Color.FromArgb(43, 43, 45);
      }
      e.Graphics.FillRectangle(new SolidBrush(hoverColor), new Rectangle(0, 0, this.Width, this.Height));
      StringFormat sf = new StringFormat();
      sf.LineAlignment = StringAlignment.Center;
      sf.Alignment = StringAlignment.Center;
      e.Graphics.DrawString(this.Text, new Font(this.Font, FontStyle.Bold), new SolidBrush(Color.FromArgb(241, 241, 241)), new Rectangle(0, 0, this.Width, this.Height), sf);
   }
}

public class CustomTextBox : TextBox
{
   public CustomTextBox()
   {
      this.BackColor = Color.FromArgb(37, 37, 38);
      this.ForeColor = Color.FromArgb(241, 241, 241);
   }
   [DllImport("user32")]
   private static extern IntPtr GetWindowDC(IntPtr hwnd);
   struct RECT
   {
      public int left, top, right, bottom;
   }
   struct NCCALSIZE_PARAMS
   {
      public RECT newWindow;
   }
   float clientPadding = 0;
   float actualBorderWidth = 1;
   Color borderColor = Color.FromArgb(67, 67, 70);
   protected override void WndProc(ref Message m)
   {
      //We have to change the clientsize to make room for borders
      //if not, the border is limited in how thick it is.
      if (m.Msg == 0x83) //WM_NCCALCSIZE   
      {
         if (m.WParam == IntPtr.Zero)
         {
            RECT rect = (RECT)Marshal.PtrToStructure(m.LParam, typeof(RECT));
            rect.left += (int)clientPadding;
            rect.right -= (int)clientPadding;
            rect.top += (int)clientPadding;
            rect.bottom -= (int)clientPadding;
            Marshal.StructureToPtr(rect, m.LParam, false);
         }
         else
         {
            NCCALSIZE_PARAMS rects = (NCCALSIZE_PARAMS)Marshal.PtrToStructure(m.LParam, typeof(NCCALSIZE_PARAMS));
            rects.newWindow.left += (int)clientPadding;
            rects.newWindow.right -= (int)clientPadding;
            rects.newWindow.top += (int)clientPadding;
            rects.newWindow.bottom -= (int)clientPadding;
            Marshal.StructureToPtr(rects, m.LParam, false);
         }
      }
      if (m.Msg == 0x85) //WM_NCPAINT    
      {
         IntPtr wDC = GetWindowDC(Handle);
         using (Graphics g = Graphics.FromHdc(wDC))
         {
            ControlPaint.DrawBorder(g, new Rectangle(0, 0, Size.Width, Size.Height), borderColor, (int)actualBorderWidth, ButtonBorderStyle.Solid,
               borderColor, (int)actualBorderWidth, ButtonBorderStyle.Solid, borderColor, (int)actualBorderWidth, ButtonBorderStyle.Solid,
               borderColor, (int)actualBorderWidth, ButtonBorderStyle.Solid);
            ControlPaint.DrawBorder(g, new Rectangle(1, 1, Size.Width - 2, Size.Height - 2), this.BackColor, (int)actualBorderWidth, ButtonBorderStyle.Solid,
               this.BackColor, (int)actualBorderWidth, ButtonBorderStyle.Solid, this.BackColor, (int)actualBorderWidth, ButtonBorderStyle.Solid,
               this.BackColor, (int)actualBorderWidth, ButtonBorderStyle.Solid);
         }
         return;
      }
      base.WndProc(ref m);
   }
}

public class CustomCheckBox : CheckBox
{
   public CustomCheckBox()
   {
      this.Paint += this.OnPaint;
      this.MouseLeave += this.OnMouseLeave;
      this.MouseEnter += this.OnMouseEnter;
   }
   private bool hover = false;
   private void OnMouseEnter(object sender, EventArgs e)
   {
      hover = true;
   }

   private void OnMouseLeave(object sender, EventArgs e)
   {
      hover = false;
   }

   private void OnPaint(object sender, PaintEventArgs e)
   {
      e.Graphics.FillRectangle(new SolidBrush(this.FindForm().BackColor), new Rectangle(0, 0, this.Width, this.Height));
      e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(37, 37, 38)), new Rectangle(0, 0, this.Height, this.Height));
      e.Graphics.DrawRectangle(new Pen(Color.FromArgb(67, 67, 70), 1), new Rectangle(0, 0, this.Height, this.Height - 1));
      StringFormat sf = new StringFormat();
      sf.LineAlignment = StringAlignment.Center;
      sf.Alignment = StringAlignment.Near;
      if (this.Checked)
         e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(57, 57, 58)), new Rectangle(3, 3, this.Height - 5, this.Height - 6));
      else if (hover)
         e.Graphics.FillRectangle(new SolidBrush(Color.FromArgb(47, 47, 48)), new Rectangle(3, 3, this.Height - 5, this.Height - 6));
      e.Graphics.DrawString(this.Text, this.Font, new SolidBrush(Color.FromArgb(241, 241, 241)), new Rectangle(21, 0, this.Width, this.Height), sf);
   }
}