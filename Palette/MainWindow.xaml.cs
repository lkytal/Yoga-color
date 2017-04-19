using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Palette
{
	/// <summary>
	/// MainWindow.xaml 的交互逻辑
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
		}

		private void Button_Click(object sender, RoutedEventArgs e)
		{

			ProcessStartInfo proArgs = new ProcessStartInfo("D:\\Code\\vc++\\ColorTmp\\Debug\\ColorTmp.exe")
			{
				CreateNoWindow = true,
				Arguments = $"{R.Value} {G.Value} {B.Value}",
				UseShellExecute = false
			};

			Process.Start(proArgs);
		}

		private void setupSlider(Slider slider, Label label)
		{
			slider.Maximum = 255;
			slider.Minimum = 225;
			slider.TickFrequency = 1;
			slider.IsSnapToTickEnabled = true;
			slider.TickPlacement = System.Windows.Controls.Primitives.TickPlacement.BottomRight;
			slider.Interval = 1;

			slider.Value = 255;

			slider.ValueChanged += (s, e) =>
			{
				label.Content = slider.Value;
			};
		}

		private void Window_Loaded(object sender, RoutedEventArgs e)
		{
			setupSlider(R, Rlabel);
			setupSlider(G, Glabel);
			setupSlider(B, Blabel);
		}
	}
}
