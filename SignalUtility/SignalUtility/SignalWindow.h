#include "GaussianBlur.h"

#pragma once

namespace SignalUtility {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for SignalWindow
	/// </summary>
	public ref class SignalWindow : public System::Windows::Forms::Form
	{
	private:
		GaussianBlur::NoiseReducerVector^ _smoothingVector;
		OpenFileDialog^ _openFileBox;
		SaveFileDialog^ _saveFileBox;
		String^ _defaultPath;
		String^ _fileName;
		bool _fileLoaded;
	private: System::Windows::Forms::Button^  btnSmoothSignal;
	private: System::Windows::Forms::ComboBox^  cboSpanOptions;
	private: System::Windows::Forms::Label^  lblVectorSpanMarker;

	private: System::Windows::Forms::Button^  btnUnsmoothSignal;
	private: System::Windows::Forms::Label^  lblMaxPeakRatioField;
	private: System::Windows::Forms::Label^  lblMaxPeakRatioMarker;
	private: System::Windows::Forms::Button^  btnSaveFlattenedSignal;
			 GaussianBlur::Sample^ _sample;
	public:
		SignalWindow(void)
		{
			InitializeComponent();
			_fileLoaded = false;
			for (int i = 1; i <= 10; i++)
			{
				cboSpanOptions->Items->Add((50 * i).ToString());
			}
			_sample = gcnew GaussianBlur::Sample();
			_smoothingVector = gcnew GaussianBlur::NoiseReducerVector();
			_defaultPath = Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments);
			_openFileBox = gcnew OpenFileDialog();
			_openFileBox->InitialDirectory = _defaultPath;
			_openFileBox->Filter = "Text Files(*.txt) | *.txt";
			_saveFileBox = gcnew SaveFileDialog();
			_saveFileBox->InitialDirectory = _defaultPath;
			_saveFileBox->Filter = "Text File(*.txt) | *.txt";
			btnSaveFlattenedSignal->Enabled = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SignalWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  SignalChart;
	private: System::Windows::Forms::Button^  btnLoadSingal;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->SignalChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->btnLoadSingal = (gcnew System::Windows::Forms::Button());
			this->btnSmoothSignal = (gcnew System::Windows::Forms::Button());
			this->cboSpanOptions = (gcnew System::Windows::Forms::ComboBox());
			this->lblVectorSpanMarker = (gcnew System::Windows::Forms::Label());
			this->btnUnsmoothSignal = (gcnew System::Windows::Forms::Button());
			this->lblMaxPeakRatioField = (gcnew System::Windows::Forms::Label());
			this->lblMaxPeakRatioMarker = (gcnew System::Windows::Forms::Label());
			this->btnSaveFlattenedSignal = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SignalChart))->BeginInit();
			this->SuspendLayout();
			// 
			// SignalChart
			// 
			chartArea1->Name = L"ChartArea1";
			this->SignalChart->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->SignalChart->Legends->Add(legend1);
			this->SignalChart->Location = System::Drawing::Point(12, 12);
			this->SignalChart->Name = L"SignalChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->Name = L"Signal";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Color = System::Drawing::Color::Red;
			series2->Legend = L"Legend1";
			series2->Name = L"Adjusted Signal";
			this->SignalChart->Series->Add(series1);
			this->SignalChart->Series->Add(series2);
			this->SignalChart->Size = System::Drawing::Size(883, 288);
			this->SignalChart->TabIndex = 0;
			this->SignalChart->Text = L"SignalChart";
			// 
			// btnLoadSingal
			// 
			this->btnLoadSingal->Location = System::Drawing::Point(12, 306);
			this->btnLoadSingal->Name = L"btnLoadSingal";
			this->btnLoadSingal->Size = System::Drawing::Size(145, 33);
			this->btnLoadSingal->TabIndex = 1;
			this->btnLoadSingal->Text = L"Load Raw Signal";
			this->btnLoadSingal->UseVisualStyleBackColor = true;
			this->btnLoadSingal->Click += gcnew System::EventHandler(this, &SignalWindow::btnLoadSingal_Click);
			// 
			// btnSmoothSignal
			// 
			this->btnSmoothSignal->Location = System::Drawing::Point(750, 306);
			this->btnSmoothSignal->Name = L"btnSmoothSignal";
			this->btnSmoothSignal->Size = System::Drawing::Size(145, 33);
			this->btnSmoothSignal->TabIndex = 2;
			this->btnSmoothSignal->Text = L"Smooth Signal";
			this->btnSmoothSignal->UseVisualStyleBackColor = true;
			this->btnSmoothSignal->Click += gcnew System::EventHandler(this, &SignalWindow::btnSmoothSignal_Click);
			// 
			// cboSpanOptions
			// 
			this->cboSpanOptions->FormattingEnabled = true;
			this->cboSpanOptions->Location = System::Drawing::Point(619, 313);
			this->cboSpanOptions->Name = L"cboSpanOptions";
			this->cboSpanOptions->Size = System::Drawing::Size(125, 21);
			this->cboSpanOptions->TabIndex = 3;
			// 
			// lblVectorSpanMarker
			// 
			this->lblVectorSpanMarker->AutoSize = true;
			this->lblVectorSpanMarker->Location = System::Drawing::Point(492, 316);
			this->lblVectorSpanMarker->Name = L"lblVectorSpanMarker";
			this->lblVectorSpanMarker->Size = System::Drawing::Size(121, 13);
			this->lblVectorSpanMarker->TabIndex = 4;
			this->lblVectorSpanMarker->Text = L"Smoothing vector width:";
			// 
			// btnUnsmoothSignal
			// 
			this->btnUnsmoothSignal->Location = System::Drawing::Point(163, 306);
			this->btnUnsmoothSignal->Name = L"btnUnsmoothSignal";
			this->btnUnsmoothSignal->Size = System::Drawing::Size(145, 33);
			this->btnUnsmoothSignal->TabIndex = 5;
			this->btnUnsmoothSignal->Text = L"Display Original Signal";
			this->btnUnsmoothSignal->UseVisualStyleBackColor = true;
			this->btnUnsmoothSignal->Click += gcnew System::EventHandler(this, &SignalWindow::btnUnsmoothSignal_Click);
			// 
			// lblMaxPeakRatioField
			// 
			this->lblMaxPeakRatioField->AutoSize = true;
			this->lblMaxPeakRatioField->Location = System::Drawing::Point(619, 337);
			this->lblMaxPeakRatioField->Name = L"lblMaxPeakRatioField";
			this->lblMaxPeakRatioField->Size = System::Drawing::Size(0, 13);
			this->lblMaxPeakRatioField->TabIndex = 7;
			// 
			// lblMaxPeakRatioMarker
			// 
			this->lblMaxPeakRatioMarker->AutoSize = true;
			this->lblMaxPeakRatioMarker->Location = System::Drawing::Point(485, 337);
			this->lblMaxPeakRatioMarker->Name = L"lblMaxPeakRatioMarker";
			this->lblMaxPeakRatioMarker->Size = System::Drawing::Size(128, 13);
			this->lblMaxPeakRatioMarker->TabIndex = 8;
			this->lblMaxPeakRatioMarker->Text = L"Ratio of greatest extrema:";
			// 
			// btnSaveFlattenedSignal
			// 
			this->btnSaveFlattenedSignal->Location = System::Drawing::Point(314, 306);
			this->btnSaveFlattenedSignal->Name = L"btnSaveFlattenedSignal";
			this->btnSaveFlattenedSignal->Size = System::Drawing::Size(145, 33);
			this->btnSaveFlattenedSignal->TabIndex = 9;
			this->btnSaveFlattenedSignal->Text = L"Save Adjusted Signal";
			this->btnSaveFlattenedSignal->UseVisualStyleBackColor = true;
			this->btnSaveFlattenedSignal->Click += gcnew System::EventHandler(this, &SignalWindow::btnSaveFlattenedSignal_Click);
			// 
			// SignalWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->ClientSize = System::Drawing::Size(907, 365);
			this->Controls->Add(this->btnSaveFlattenedSignal);
			this->Controls->Add(this->lblMaxPeakRatioMarker);
			this->Controls->Add(this->lblMaxPeakRatioField);
			this->Controls->Add(this->btnUnsmoothSignal);
			this->Controls->Add(this->lblVectorSpanMarker);
			this->Controls->Add(this->cboSpanOptions);
			this->Controls->Add(this->btnSmoothSignal);
			this->Controls->Add(this->btnLoadSingal);
			this->Controls->Add(this->SignalChart);
			this->Name = L"SignalWindow";
			this->Text = L"Signal Noise Adjuster";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SignalChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		// Control: "Load Raw Signal" button
		// Initializes display values and private members. Displays an Open File
		// dialog box and loads selected data into the form for display on the chart.
		System::Void btnLoadSingal_Click(System::Object^  sender, System::EventArgs^  e) {
			// Set controls as though no file has been loaded.
			 lblMaxPeakRatioField->Text = "";
			 SignalChart->Series["Signal"]->Points->Clear();
			 SignalChart->Series["Adjusted Signal"]->Points->Clear();
			 btnSaveFlattenedSignal->Enabled = false;
			 // Set private members.
			 _fileLoaded = false;
			 _openFileBox->FileName = "";
			 _fileName = "";
			 // Exit the method if the user does not select a file to load.
			 if (_openFileBox->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			 {
				 return;
			 }
			 // Initialize variables for the sample load operation.
			 int lastIndex;
			 Stream^ chosenFile;
			 array<String^>^ filePath;
			 array<wchar_t>^ delimiters = { '\\', '.' };
			 filePath = _openFileBox->FileName->Split(delimiters);
			 _fileLoaded = true;
			 // Cache the file name to expedite saving; may be relevant in other areas in future development.
			 _fileName = filePath[filePath->Length - 2];
			 _saveFileBox->FileName = _fileName + "_ADJUSTED";
			 chosenFile = _openFileBox->OpenFile();
			 // Start reading data.
			 StreamReader^ inFile = gcnew StreamReader(chosenFile);
			 // Begin with the sample size.
			 long sampleSize;
			 String^ inLine = inFile->ReadLine();
			 sampleSize = long::Parse(inLine);
			 _sample->Reset(sampleSize);
			 // Start reading in points.
			 double pointX;
			 double pointY;
			 array<String^>^ coordinates;
			 for (int i = 0; i < sampleSize && (inFile->Peek() >= 0); i++)
			 {
				 inLine = inFile->ReadLine();
				 // Data points are presumed to be ordered pairs delimited by white space.
				 // This white space could be more than one character, so we select the first
				 // and last elements in the Split array when designating points.
				 coordinates = inLine->Split();
				 lastIndex = (coordinates->Length - 1);
				 pointX = double::Parse(coordinates[0]);
				 pointY = double::Parse(coordinates[lastIndex]);
				 _sample->SetPoint(i, pointX, pointY);
			 }
			 // Close the streams.
			 inFile->Close();
			 chosenFile->Close();
			 // Display the signal.
			 displayRawSignal();
	}
	// Private Method: displayRawSignal
	// Returns: Void
	// Assumes: A signal has been loaded from file.
	// Clears the chart and loads only the raw signal data. Displays
	// an extrema ratio of 1 since the signal has not been adjusted.
	System::Void displayRawSignal()
	{
		btnSaveFlattenedSignal->Enabled = false;
		SignalChart->Series["Signal"]->Points->Clear();
		SignalChart->Series["Adjusted Signal"]->Points->Clear();
		for (int i = 0; i < _sample->Size; i++)
		{
			this->SignalChart->Series["Signal"]->Points->AddXY(_sample->PointX(i), _sample->PointY(i));
		}
		lblMaxPeakRatioField->Text = "1";
	}
	// Private Method: displayUpdatedSignal
	// Returns: Void
	// Assumes: Raw signal data has been loaded.
	// Checks to see if a smoothing operation has been performed
	// on the data. If so, clears the chart of any existing
	// smoothed signal data and redraws it using a single buffer.
	// Also determines the highest absolute value of any point in
	// the raw and smoothed signals and displays their ratio
	// (if defined,) to allow the user to gauge the impact of
	// smoothing on the relevant resolution of the signal.
	System::Void displayUpdatedSignal()
	{
		double maxOfRawSample = 0.0;
		double maxOfSmoothedSample = 0.0;
		String^ maxRatioField;
		if (!_sample->WasSmoothed())
		{
			return;
		}
		SignalChart->Series["Adjusted Signal"]->Points->Clear();
		for (int i = 0; i < _sample->Size; i++)
		{
			this->SignalChart->Series["Adjusted Signal"]->Points->AddXY(_sample->PointX(i), _sample->SmoothedPointY(i));
			maxOfRawSample = Math::Max(Math::Abs(_sample->PointY(i)), maxOfRawSample);
			maxOfSmoothedSample = Math::Max(Math::Abs(_sample->SmoothedPointY(i)), maxOfSmoothedSample);
		}

		if (maxOfRawSample > 0.0)
		{
			maxRatioField = (maxOfSmoothedSample / maxOfRawSample).ToString();
			lblMaxPeakRatioField->Text = String::Format("{0:g}", maxRatioField);
		}
		else
		{
			lblMaxPeakRatioField->Text = "Undefined";
		}
		// If the display was successful, permit the user to save the smoothed data to file.
		btnSaveFlattenedSignal->Enabled = true;
	}
	// Control: "Smooth Signal" button
	// If a signal has been loaded, displays a signal which
	// has been adjusted using a Gaussian blur to reduce noise.
	// If a smoothing operation has already been performed, the
	// existing result is used unless a new vector width has been
	// selected, in which case the new vector is generated and
	// applied to the raw data to generate the curve.
	private: System::Void btnSmoothSignal_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (!_fileLoaded || String::IsNullOrWhiteSpace(cboSpanOptions->Text))
				 {
					 return;
				 }
				 int span = int::Parse(cboSpanOptions->Text);
				 if (span != _smoothingVector->Size)
				 {
					 _smoothingVector->ResetSpan(span);
				 }
				 _sample->SmoothSample(_smoothingVector);
				 displayUpdatedSignal();
	}
			 // Control: "Display Original Signal" button
			 // Checks to determine if a signal has been loaded by the user,
			 // then clears the chart and displays the raw data if it exists.
private: System::Void btnUnsmoothSignal_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (_fileLoaded)
			 {
				 displayRawSignal();
			 }
}
		 // Control: "Save Adjusted Signal" button
		 // Checks to see if a file has been loaded, then calls
		 // a Save File dialog box. If the user opts to save a file,
		 // saves the adjusted signal as lines of coordinate pairs
		 // delimited by whitespace in a text file.
private: System::Void btnSaveFlattenedSignal_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (String::IsNullOrEmpty(_fileName))
			 {
				 return;
			 }
			 // Additional file load failsafe.
			 if (!_fileLoaded)
			 {
				 return;
			 }
			 if (_saveFileBox->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			 {
				 return;
			 }
			 StreamWriter^ tempWriter = gcnew StreamWriter(_saveFileBox->OpenFile());
			 if (tempWriter == nullptr)
			 {
				 return;
			 }
			 String^ xVal;
			 String^ yVal;
			 // Don't write the sample size: that was necessary to perform
			 // operations on the signal, but including anything other than the
			 // raw data makes unsafe assumptions about the information the user needs.
			 for (long i = 0; i < _sample->Size; i++)
			 {
				 // Although the file is intended to be minimally formatted,
				 // values were separated by two spaces to match the format used
				 // in QuadFit, which is used by the Coe College Physics Department
				 // to model NMR spectra.
				 xVal = _sample->PointX(i).ToString();
				 yVal = _sample->SmoothedPointY(i).ToString();
				 tempWriter->Write(xVal + "  " + yVal + "\n");
			 }
			 tempWriter->Close();
}
};
}
