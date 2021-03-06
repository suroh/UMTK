#include "mainwindow.h"
#include "./ui_mainwindow.h"


#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    main_frame = new QFrame(this);
    key_widget = new QStackedWidget();
    key_widget->addWidget(mainwidget.get_widget());
    key_widget->insertWidget(1, domainwidget.get_widget());
    key_widget->insertWidget(2, localwidget.get_widget());
    //key_widget->insertWidget(2, editwidget.get_widget());
    initialize_main_window();
    initialize_actions();
    initialize_menus();
    initialize_connections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize_main_window()
{
    setCentralWidget(key_widget);
    setWindowTitle("User Maintenance Tool Kit");
}


void MainWindow::initialize_connections()
{
      //connect(saveFileAction, &QAction::triggered, this, &MainWindow::save_command);
      connect(setDisplayNameAction, &QAction::triggered, [this] {if(setDisplayNameAction->isChecked()) { domainwidget.display_name_edit->show();} if(!setDisplayNameAction->isChecked()) {domainwidget.display_name_edit->hide();} });
      connect(setProxyAction, &QAction::triggered, [this] {if (setProxyAction->isChecked()) { domainwidget.primary_proxy_edit->show(); domainwidget.secondary_proxy_edit->show(); } if(!setProxyAction->isChecked()) {domainwidget.primary_proxy_edit->hide(); domainwidget.secondary_proxy_edit->hide(); } } );
      connect(setDisplayNameAction, &QAction::triggered, [this] { if(setDisplayNameAction->isChecked()) { domainwidget.display_name_edit->show(); } if(!setDisplayNameAction->isChecked()) { domainwidget.display_name_edit->hide(); } } );
      //connect(serverwidget.create_button, &QPushButton::clicked, this, &MainWindow::initialize_warning_banner);
      connect(mainwidget.server_button, &QPushButton::clicked, this, &MainWindow::launch_server_widget);
      connect(domainwidget.create_button, &QPushButton::clicked, this, &MainWindow::create_domain_user);
      connect(domainwidget.cancel_button, &QPushButton::clicked, this, &MainWindow::close_server_widget);
      connect(mainwidget.local_button, &QPushButton::clicked, this, &MainWindow::launch_local_widget);
      connect(localwidget.cancel_button, &QPushButton::clicked, this, &MainWindow::close_local_widget);
      connect(localwidget.create_button, &QPushButton::clicked, this, &MainWindow::create_local_user);

}

 void MainWindow::initialize_actions()
 {
     saveFileAction = new QAction(tr("Save Command"));
     saveFileAction->setShortcuts(QKeySequence::New);
     saveFileAction->setStatusTip(tr("Click this to save your current command."));
     saveFileAction->setToolTip("Save your current working command to a StringList for future use.");


     saveFileAsAction = new QAction(tr("Save to file"));
     saveFileAsAction->setStatusTip(tr("Click this to save your current command to an existing ps script."));
     saveFileAsAction->setToolTip("Save your current working command to a new ps script.");

     closeProgramAction = new QAction(tr("Close program"));
     closeProgramAction->setStatusTip("Click this to close the program");
     closeProgramAction->setToolTip("Click to close the program.");

     setProxyAction = new QAction("Set aditonal proxy");
     setProxyAction->setToolTip("Check this to show a widget that will enable you to add a non-standard primary\nandsecondary proxy address.");
     setProxyAction->setStatusTip("Check this to show a widget that will enable you to add a non-standard primary\nandsecondary proxy address.");
     setProxyAction->setCheckable(true);

     setDisplayNameAction = new QAction("Set display name");
     setDisplayNameAction->setToolTip("Check this to enable a widget to modify the display name.");
     setDisplayNameAction->setStatusTip("Check this to enable a widget to modify the display name.");
     setDisplayNameAction->setCheckable(true);

     helpMeAction = new QAction(tr("Help"));
     helpMeAction->setToolTip("Click to view the help documentation.");
     helpMeAction->setToolTip("Click to view the help documentation.");

 }

 void MainWindow::initialize_menus()
 {
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(saveFileAction);
        fileMenu->addSeparator();
        fileMenu->addAction(saveFileAsAction);
        fileMenu->addSeparator();
        fileMenu->addAction(closeProgramAction);
        fileMenu->setToolTipsVisible(true);

        editMenu = menuBar()->addMenu(tr("&Edit"));



        settingsMenu = menuBar()->addMenu(tr("&Settings"));
        settingsMenu->addAction(setProxyAction);
        settingsMenu->addSeparator();
        settingsMenu->addAction(setDisplayNameAction);

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(helpMeAction);

        fileMenu->setToolTipsVisible(true);
        editMenu->setToolTipsVisible(true);
        settingsMenu->setToolTipsVisible(true);
        helpMenu->setToolTipsVisible(true);
 }

 void MainWindow::launch_local_widget()
 {
     key_widget->setCurrentIndex(2);
 }

 void MainWindow::launch_server_widget()
 {
     key_widget->setCurrentIndex(1);
 }

 void MainWindow::launch_edit_user_widget()
 {

 }

 void MainWindow::close_local_widget()
 {
     key_widget->setCurrentIndex(0);
 }

 void MainWindow::close_server_widget()
 {
     key_widget->setCurrentIndex(0);
 }

 void MainWindow::close_edit_user_widget()
 {

 }

 void MainWindow::create_local_user()
 {
     Local_User luser;
     if(localwidget.username_edit->text() <= 0)
     {
         localwidget.username_edit->setStyleSheet("color: black; background-color: red");
         localwidget.username_edit->setPlaceholderText("VALUE CANNOT BE EMPTY");
     }
     else if(localwidget.username_edit->text() > 0)
     {
         localwidget.username_edit->setStyleSheet("color: black; background-color: white");
         luser.username = localwidget.username_edit->text();
     }

     if(localwidget.fullname_edit->text() <= 0)
     {
         localwidget.fullname_edit->setStyleSheet("color: black; background-color: red");
         localwidget.fullname_edit->setPlaceholderText("VALUE CANNOT BE EMPTY");
     }
     else if(localwidget.fullname_edit->text() > 0)
     {
         localwidget.fullname_edit->setStyleSheet("color: black; background-color: white");
         luser.employee_name = localwidget.fullname_edit->text();
     }

     if(localwidget.emailaddress_edit->text() <= 0)
     {
         localwidget.emailaddress_edit->setStyleSheet("color: black; background-color: red");
         localwidget.emailaddress_edit->setPlaceholderText("VALUE CANNOT BE EMPTY");
     }
     else if(localwidget.emailaddress_edit->text() > 0)
     {
         localwidget.emailaddress_edit->setStyleSheet("color: black; background-color: white");
         luser.email_address = localwidget.emailaddress_edit->text();
     }
     if(localwidget.password_edit->text() <= 0)
     {
         localwidget.password_edit->setStyleSheet("color: black; background-color: red");
         localwidget.password_edit->setPlaceholderText("VALUE CANNOT BE EMPTY");
     }
     else if(localwidget.password_edit->text() > 0)
     {
         localwidget.password_edit->setStyleSheet("color: black; background-color: white");
         luser.password = localwidget.password_edit->text();
     }

     if(localwidget.admin_checkbox->isChecked())
     {
         luser.is_administrator = "1";
     }
     else if(!localwidget.admin_checkbox->isChecked())
     {
         luser.is_administrator = "0";
     }

     if(luser.username > 0 && luser.employee_name > 0 && luser.email_address > 0 && luser.password > 0)
     {
         QString tmp = "net user /add " + luser.username + " " + luser.password;
         elevate_and_execute(tmp);
     }
 }

 void MainWindow::create_domain_user()
 {
    Domain_User duser;
    if(domainwidget.employee_name_edit->text().length() <= 0)
    {
        domainwidget.employee_name_edit->setStyleSheet("color: black; background-color: red");
        domainwidget.employee_name_edit->setPlaceholderText("VALUE CANNOT BE EMPTY");
    }
    else if(domainwidget.employee_name_edit->text() > 0)
    {
        duser.employe_name = domainwidget.employee_name_edit->text();
        duser.display_name = domainwidget.employee_name_edit->text();
        QStringList name = duser.employe_name.split(" ");
        duser.given_name = name.first();
        duser.surname = name.last();
    }
    if(domainwidget.user_edit->text().length() <= 0)
    {
        domainwidget.user_edit->setStyleSheet("color: black; background-color: red");
        domainwidget.user_edit->setPlaceholderText("VALUE CANNOT BE EMPTY");
    }
    else if(domainwidget.user_edit->text().length() > 0)
    {
        duser.sam_name = domainwidget.user_edit->text();
    }
    if(domainwidget.password_edit->text().length() <= 0)
    {
        domainwidget.password_edit->setStyleSheet("color: black; background-color: red");
        domainwidget.password_edit->setPlaceholderText("VALUE CANNOT BE EMPTY");
    }
    else if(domainwidget.password_edit->text().length() > 0)
    {
        duser.password = "\"" + domainwidget.password_edit->text() + "\"";
    }
    if(domainwidget.email_edit->text().length() <= 0)
    {
        domainwidget.email_edit->setStyleSheet("color: black; background-color: red");
        domainwidget.email_edit->setPlaceholderText("VALUE CANNOT BE EMPTY");
    }
    else if(domainwidget.email_edit->text().length() > 0)
    {
        duser.email_address = domainwidget.email_edit->text();
        duser.proxy_addresses << domainwidget.email_edit->text();
    }
    if(duser.employe_name.length() > 0 && duser.sam_name.length() > 0 && duser.password.length() > 0 && duser.email_address.length() > 0)
    {

        QString p = "$p = " + duser.password + "; $sec = $p | ConvertTo-SecureString -AsPlainText -Force; ";
        duser.ou_clean = domainwidget.ou_combo->currentText();


        duser.ou_actual = "\"" + domainwidget.ou_distinguished_names.at(domainwidget.ou_combo->currentIndex()) + "\"";

        bool bad_chars = true;
        while(bad_chars)
        {
            if(duser.ou_actual.contains("\r"))
            {
                duser.ou_actual = duser.ou_actual.remove(QChar('\r'));
            }
            if(duser.ou_actual.contains("\n"))
            {
                duser.ou_actual = duser.ou_actual.remove(QChar('\n'));
            }
            if(!duser.ou_actual.contains("\r") && !duser.ou_actual.contains("\n"))
            {
                bad_chars = false;
            }
        }

        duser.template_user = domainwidget.template_user_combo->currentText();

        bad_chars = true;
        while(bad_chars)
        {
            if(duser.template_user.contains("\r"))
            {
                duser.template_user = duser.template_user.remove(QChar('\r'));
            }
            if(duser.template_user.contains("\n"))
            {
                duser.template_user = duser.template_user.remove(QChar('\n'));
            }
            if(!duser.template_user.contains("\r") && !duser.template_user.contains("\n"))
            {
                bad_chars = false;
            }
        }



        if(duser.UPN.length() <= 0)
        {
            duser.userpname = duser.sam_name + "@" + domainwidget.domain_name_combo->currentText();
            duser.userpname.remove(QChar('"'));
        }
        else if(duser.UPN.length() > 0)
        {
            duser.userpname = duser.sam_name + duser.UPN;
        }
        if(domainwidget.primary_proxy_edit->text().length() > 0)
        {
            duser.proxy_addresses << domainwidget.primary_proxy_edit->text();
        }
        if(domainwidget.secondary_proxy_edit->text().length() > 0)
        {
            duser.proxy_addresses << domainwidget.secondary_proxy_edit->text();
        }

        duser.complete_command = p + "New-ADUser -Name " + "\"" + duser.employe_name +"\"" + " -GivenName " + "\"" + duser.given_name + "\""
                + " -Surname " + "\"" + duser.surname + "\"" + " -AccountPassword $sec " + " -UserPrincipalName " + "\"" + duser.userpname + "\""
                " -DisplayName " + "\"" + duser.display_name + "\"" + " -EmailAddress " + "\"" + duser.email_address + "\"" + " -SamAccountName " +
                "\"" + duser.sam_name + "\"" + " -Enabled " + duser.is_enabled;


        duser.set_groups_command = "$tmp = (Get-ADUser -Filter {Name -like \"" + duser.template_user + "\"}); "
                                   "$groups = (Get-ADUser $tmp -Properties MemberOf).MemberOf; $usr = \"" + duser.sam_name + "\"; "
                                   "Foreach ($group in $groups) {Add-ADGroupMember -Identity (Get-ADGroup $group).name -Members $usr} ";

        warning_banner = new QMessageBox();
        QPushButton *okay_button = warning_banner->addButton(tr("Okay"), QMessageBox::ActionRole);
        QPushButton *cancel_button = warning_banner->addButton(tr("Cancel"), QMessageBox::ActionRole);
        warning_banner->setText("Confirm the following by clicking 'Okay'\nTo cancel and redo, click 'Cancel'");

        if (domainwidget.primary_proxy_edit->isHidden())
        {
            if(domainwidget.primary_proxy_edit->text().length() > 0 && domainwidget.secondary_proxy_edit->text().length() > 0)
            {
                if(domainwidget.display_name_edit->isHidden())
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nPrimary proxy: " + duser.proxy_addresses.first() + "\nSecondary Proxy: " + duser.proxy_addresses.last());
                }
                else if(!domainwidget.display_name_edit->isHidden() && domainwidget.display_name_edit->text().length() > 0)
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDisplay name" + duser.display_name + "\nPrimary proxy: " + duser.proxy_addresses.first() + "\nSecondary Proxy: " + duser.proxy_addresses.last());
                }
            }
            if(domainwidget.primary_proxy_edit->text().length() <= 0 && domainwidget.secondary_proxy_edit->text().length() > 0)
            {
                if(domainwidget.display_name_edit->isHidden())
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nPrimary proxy: " + "SMTP:" + duser.email_address + "\nSecondary Proxy: " + duser.proxy_addresses.last());
                }
                else if(!domainwidget.display_name_edit->isHidden() && domainwidget.display_name_edit->text().length() > 0)
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDisplay name" + duser.display_name + "\nPrimary proxy: " + "SMTP:" + duser.email_address + "\nSecondary Proxy: " + duser.proxy_addresses.last());
                }
            }
            if(domainwidget.primary_proxy_edit->text().length() > 0 && domainwidget.secondary_proxy_edit->text().length() <= 0)
            {
                if(domainwidget.display_name_edit->isHidden())
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nPrimary proxy: " + duser.proxy_addresses.first());
                }
                else if(!domainwidget.display_name_edit->isHidden() && domainwidget.display_name_edit->text().length() > 0)
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDisplay name" + duser.display_name + "\nPrimary proxy: " + duser.proxy_addresses.first());
                }
            }
            if(domainwidget.primary_proxy_edit->text().length() <= 0 && domainwidget.secondary_proxy_edit->text().length() <= 0)
            {
                if(domainwidget.display_name_edit->isHidden())
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDefault proxy: " + "SMTP:" + duser.email_address);
                }
                else if(!domainwidget.display_name_edit->isHidden() && domainwidget.display_name_edit->text().length() > 0)
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDisplay name" + duser.display_name + "\nDefault proxy: " + "SMTP:" + duser.email_address);
                }
            }

        }
        else if(!domainwidget.primary_proxy_edit->isHidden())
        {
            if(domainwidget.primary_proxy_edit->text().length() > 0 && domainwidget.secondary_proxy_edit->text().length() > 0)
            {
                if(domainwidget.display_name_edit->isHidden())
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nPrimary proxy: " + duser.proxy_addresses.first() + "\nSecondary Proxy: " + duser.proxy_addresses.last());
                }
                else if(!domainwidget.display_name_edit->isHidden() && domainwidget.display_name_edit->text().length() > 0)
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDisplay name" + duser.display_name + "\nPrimary proxy: " + duser.proxy_addresses.first() + "\nSecondary Proxy: " + duser.proxy_addresses.last());
                }
            }
            if(domainwidget.primary_proxy_edit->text().length() <= 0 && domainwidget.secondary_proxy_edit->text().length() > 0)
            {
                if(domainwidget.display_name_edit->isHidden())
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nPrimary proxy: " + "SMTP:" + duser.email_address + "\nSecondary Proxy: " + duser.proxy_addresses.last());
                }
                else if(!domainwidget.display_name_edit->isHidden() && domainwidget.display_name_edit->text().length() > 0)
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDisplay name" + duser.display_name + "\nPrimary proxy: " + "SMTP:" + duser.email_address + "\nSecondary Proxy: " + duser.proxy_addresses.last());
                }
            }
            if(domainwidget.primary_proxy_edit->text().length() > 0 && domainwidget.secondary_proxy_edit->text().length() <= 0)
            {
                if(domainwidget.display_name_edit->isHidden())
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nPrimary proxy: " + duser.proxy_addresses.first());
                }
                else if(!domainwidget.display_name_edit->isHidden() && domainwidget.display_name_edit->text().length() > 0)
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDisplay name" + duser.display_name + "\nPrimary proxy: " + duser.proxy_addresses.first());
                }
            }
            if(domainwidget.primary_proxy_edit->text().length() <= 0 && domainwidget.secondary_proxy_edit->text().length() <= 0)
            {
                if(domainwidget.display_name_edit->isHidden())
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDefault proxy: " + "SMTP:" + duser.email_address);
                }
                else if(!domainwidget.display_name_edit->isHidden() && domainwidget.display_name_edit->text().length() > 0)
                {
                    warning_banner->setInformativeText("Employee Name: " + duser.employe_name +"\nUsername: " + duser.sam_name + "\nPassword: " + duser.password + "\nEmail Address: " + duser.email_address + "\nDisplay name" + duser.display_name + "\nDefault proxy: " + "SMTP:" + duser.email_address);
                }
            }
        }


        warning_banner->exec();
        if(warning_banner->clickedButton() == okay_button)
        {
            elevate_and_execute(duser.complete_command);

            elevate_and_execute(duser.set_groups_command);


            if(domainwidget.primary_proxy_edit->text().length() > 0 && domainwidget.secondary_proxy_edit->text().length() > 0)
            {
                elevate_and_execute("Set-ADUser -Identity " + QString("\"") + duser.sam_name + QString("\"") + " -Add @{Proxyaddresses = " + "\"SMTP:" + duser.proxy_addresses.first() + "\"}");
                elevate_and_execute("Set-ADUser -Identity " + QString("\"") + duser.sam_name + QString("\"") +  " -Add @{Proxyaddresses = " + "\"smtp:" + duser.proxy_addresses.last() + "\"}");
            }
            else if(domainwidget.primary_proxy_edit->text().length() > 0 && domainwidget.secondary_proxy_edit->text().length() <= 0)
            {
                elevate_and_execute("Set-ADUser -Identity " + QString("\"") + duser.sam_name + QString("\"") + " -Add @{Proxyaddresses = " + "\"SMTP:" + duser.proxy_addresses.first() +"\"}");
            }
            else if(domainwidget.secondary_proxy_edit->text().length() > 0 && domainwidget.primary_proxy_edit->text().length() <= 0)
            {
                elevate_and_execute("Set-ADUser -Identity " + QString("\"") + duser.sam_name + QString("\"") +  " -Add @{Proxyaddresses = " + "\"SMTP:" + duser.email_address +"\"}");
                elevate_and_execute("Set-ADUser -Identity " + QString("\"") + duser.sam_name + QString("\"") +  " -Add @{Proxyaddresses = " + "\"smtp:" + duser.proxy_addresses.last() +"\"}");
            }
            else if(domainwidget.secondary_proxy_edit->text().length() <= 0 && domainwidget.primary_proxy_edit->text().length() <= 0)
            {
                write_debug_logs("Set-ADUser -Identity \"" + duser.sam_name + "\" -Add @{Proxyaddresses = " + "\"SMTP:" + duser.email_address +"\"}");
                elevate_and_execute("Set-ADUser -Identity \"" + duser.sam_name + "\" -Add @{Proxyaddresses = " + "\"SMTP:" + duser.email_address +"\"}");
            }

            shift_ou("$user = (Get-ADUser -Filter {SamAccountName -like \"" + duser.sam_name + "\"} | Select-Object -ExpandProperty DistinguishedName);", duser.ou_actual);
        }
        else if (warning_banner->clickedButton() == cancel_button)
        {
            clear_ui();
        }

        // REMOVAL LINE

    }

 }


 void MainWindow::clear_ui()
 {
     domainwidget.employee_name_edit->setText("");
     domainwidget.user_edit->setText("");
     domainwidget.password_edit->setText("");
     domainwidget.email_edit->setText("");
     domainwidget.display_name_edit->setText("");
     domainwidget.primary_proxy_edit->setText("");
     domainwidget.secondary_proxy_edit->setText("");
 }

 void MainWindow::write_debug_logs(QString datastring) // remove
 {
     QFile data("path\\to\\output.txt");
     if (data.open(QFile::WriteOnly)) {
         QTextStream out(&data);
         out << datastring;

     }
 }

 void MainWindow::elevate_and_execute(QString param)
 {
     QProcess *process = new QProcess();
     QStringList params = QStringList();
     QByteArray output; // remove

     params = QStringList({"-Command", QString("Start-Process -Verb runAs powershell; "), param});
     process->start("powershell", params);
     process->waitForFinished();
     output = process->readAllStandardError(); // remove
     qDebug() << output; // remove
     process->terminate();

 }


void MainWindow::shift_ou(QString command, QString OU)
{
    elevate_and_execute(command + "Move-ADObject -Identity $user -TargetPath " + OU);
}
