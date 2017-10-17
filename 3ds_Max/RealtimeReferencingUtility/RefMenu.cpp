#include "RefMenu.h"
#include "ui_ref_menu.h"


#define Controller SceneController::Instance()


RefMenu::RefMenu(QWidget* parent):QWidget(/*parent*/), ui(new Ui::RefMenuRollup())
{

	ui->setupUi(this);
	ui->pathEdit->setText("C:/Temp");

	//Connect Buttons to functions
	connect(ui->pathButton, &QPushButton::clicked, [this] {OpenPathExplorer(); });
	connect(ui->createNodeButton, &QPushButton::clicked, [this] {CreateButtonClicked(); });
	connect(ui->removeNodeButton, &QPushButton::clicked, [this] {RemoveButtonClicked(); });
	
	connect(ui->updateButton, &QPushButton::clicked, [this] {Controller->Update("_refRoot.json"); });
	//connect(ui->createNodeButton, &QPushButton::clicked, [this] {Controller->CreateObject(ui->pathEdit->text().toLatin1().data(), "test"); });



	//TESTS!!!!
	connect(ui->testButton, &QPushButton::clicked, [this] {Controller->TestFunction(); });
}


RefMenu::~RefMenu(void)
{
	delete ui;
}

void RefMenu::OpenPathExplorer() {
	QFileDialog *fd = new QFileDialog;
	fd->setFileMode(QFileDialog::Directory);
	fd->setOption(QFileDialog::ShowDirsOnly);
	fd->setViewMode(QFileDialog::Detail);
	fd->setDirectory(ui->pathEdit->text());
	int result = fd->exec();
	QString directory;
	if (result)
	{
		directory = fd->selectedFiles()[0];
		ui->pathEdit->setText(directory);
	}

}

void RefMenu::CreateButtonClicked() {

	if (fileExists(ui->pathEdit->text() + "/_refRoot.json")) {
		AddFileWatcher();
		//Update UI
		ui->createNodeButton->setDisabled(true);
		ui->removeNodeButton->setDisabled(false);
		ui->updateButton->setDisabled(false);
		ui->autoUpdateCheck->setDisabled(false);

		Controller->CreateRefScene(ui->pathEdit->text().toLatin1().data());
	}
	else {
		QMessageBox::information(
			this,
			tr("Realtime Referencing"),
			tr("No References found in selected path!"));
	}
	
}

void RefMenu::RemoveButtonClicked() {
	ui->createNodeButton->setDisabled(false);
	ui->removeNodeButton->setDisabled(true);
	ui->updateButton->setDisabled(true);
	ui->autoUpdateCheck->setDisabled(true);
	Controller->DeleteRefScene();
}

void RefMenu::AddFileWatcher() {
	watcher = new QFileSystemWatcher();
	watcher->addPath(ui->pathEdit->text());
	watcher->addPath(ui->pathEdit->text()+"/_refRoot.json");

	QStringList directoryList = watcher->directories();
	Q_FOREACH(QString directory, directoryList)
		qDebug() << "Directory name" << directory << "\n";

	QObject::connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(showModified(QString)));
}

void RefMenu::showModified(const QString& str)
{
	wchar_t *wchar = new wchar_t[str.length() + 1];
	str.toWCharArray(wchar);
	wchar[str.length()] = 0;
	QString refR = ui->pathEdit->text() + "/_refRoot.json";
	if (str == refR) {
		Controller->Print(L"Yeah");
		Controller->Update("_refRoot.json");
	}
	else {
		Controller->Print(wchar);
		std::string s = str.toStdString();
		const char* p = s.c_str();
		Controller->Update(p);
	}
}

bool RefMenu::fileExists(QString path) {
	QFileInfo check_file(path);
	// check if file exists and if yes: Is it really a file and no directory?
	if (check_file.exists() && check_file.isFile()) {
		return true;
	}
	else {
		return false;
	}
}