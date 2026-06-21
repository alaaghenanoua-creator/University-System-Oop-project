#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QGroupBox>
#include <QStatusBar>
#include <QTimer>
#include <QTextCursor>
#include <QFont>
#include <QStackedWidget>
#include <QFrame>
#include <QScrollArea>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QDialog>
#include <QPainter>
#include <QLinearGradient>
#include <QBrush>
#include <QPalette>
#include <QGraphicsDropShadowEffect>
#include <QComboBox>
#include <QSpinBox>
#include <QListWidget>
#include <QMap>
#include <QVector>
#include <QTabWidget>
#include <QCheckBox>
#include <QPropertyAnimation>
#include <QEasingCurve>

#include "University.h"
#include "Student.h"
#include "Dormitory.h"
#include "Room.h"
#include "Restaurant.h"

// ============================================================
// UNIVERSITY THEME BACKGROUND
// ============================================================

class UniversityBackground : public QWidget {
public:
    UniversityBackground(QWidget *parent = nullptr) : QWidget(parent) {
        setAutoFillBackground(true);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor(10, 15, 30));
        gradient.setColorAt(0.3, QColor(20, 30, 60));
        gradient.setColorAt(0.6, QColor(30, 20, 50));
        gradient.setColorAt(0.8, QColor(15, 35, 45));
        gradient.setColorAt(1, QColor(10, 20, 35));
        painter.fillRect(rect(), gradient);

        painter.setPen(Qt::NoPen);

        painter.setBrush(QBrush(QColor(255, 215, 0, 8)));
        int bw = 500, bh = 300;
        int x = width() - bw - 100;
        int y = height() - bh - 60;
        painter.drawRect(x, y, bw, bh);

        painter.setBrush(QBrush(QColor(255, 215, 0, 12)));
        for (int i = 0; i < 6; i++) {
            painter.drawRect(x + 30 + i * 80, y + bh - 50, 20, 50);
        }

        painter.setBrush(QBrush(QColor(255, 215, 0, 15)));
        QPolygon roof;
        roof << QPoint(x - 30, y) << QPoint(x + bw/2, y - 80) << QPoint(x + bw + 30, y);
        painter.drawPolygon(roof);

        painter.setBrush(QBrush(QColor(255, 215, 0, 20)));
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 4; j++) {
                painter.drawRect(x + 40 + i * 80, y + 25 + j * 55, 40, 40);
            }
        }

        painter.setBrush(QBrush(QColor(255, 215, 0, 15)));
        painter.drawEllipse(-150, -150, 400, 400);
        painter.drawEllipse(width() - 250, 50, 350, 350);

        painter.setBrush(QBrush(QColor(255, 215, 0, 10)));
        painter.drawEllipse(width()/2 - 200, height() - 250, 300, 300);

        painter.setBrush(QBrush(QColor(255, 215, 0, 20)));
        for (int i = 0; i < 40; i++) {
            int x = rand() % width();
            int y = rand() % height();
            int size = 1 + rand() % 4;
            painter.drawEllipse(x, y, size, size);
        }

        painter.setPen(QPen(QColor(255, 215, 0, 20), 2));
        painter.drawLine(50, height() - 50, 250, height() - 50);
        painter.setPen(QPen(QColor(255, 215, 0, 15), 1));
        painter.drawLine(width() - 250, 50, width() - 50, 50);

        painter.end();
    }
};

// Login Background
class LoginBackgroundUniversity : public QWidget {
public:
    LoginBackgroundUniversity(QWidget *parent = nullptr) : QWidget(parent) {
        setAutoFillBackground(true);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor(10, 15, 30));
        gradient.setColorAt(0.3, QColor(20, 30, 60));
        gradient.setColorAt(0.6, QColor(30, 20, 50));
        gradient.setColorAt(1, QColor(10, 20, 35));
        painter.fillRect(rect(), gradient);

        painter.setPen(Qt::NoPen);

        painter.setBrush(QBrush(QColor(255, 215, 0, 20)));
        painter.drawEllipse(-200, -200, 500, 500);
        painter.drawEllipse(width() - 300, -50, 400, 400);
        painter.drawEllipse(width()/2 - 150, height() - 250, 300, 300);

        painter.setBrush(QBrush(QColor(255, 215, 0, 8)));
        for (int i = 0; i < 3; i++) {
            painter.drawEllipse(width()/2 - 180 + i * 20, height()/2 - 180 + i * 20,
                                360 - i * 40, 360 - i * 40);
        }

        painter.setPen(QPen(QColor(255, 215, 0, 30), 2));
        painter.drawLine(width()/2 - 150, height() - 100, width()/2 + 150, height() - 100);

        painter.end();
    }
};

// ============================================================
// LOGIN DIALOG
// ============================================================

class LoginDialog : public QDialog {
    Q_OBJECT
private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QString loggedInUser;

public:
    LoginDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("🏛️ University Management System - Login");
        setFixedSize(600, 720);
        setModal(true);
        setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        setAttribute(Qt::WA_TranslucentBackground);
        setupUI();
    }

    QString getLoggedInUser() const { return loggedInUser; }

private:
    void setupUI() {
        LoginBackgroundUniversity *background = new LoginBackgroundUniversity(this);
        background->setGeometry(0, 0, 600, 720);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setSpacing(0);
        mainLayout->setContentsMargins(60, 60, 60, 60);

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(60);
        shadow->setColor(QColor(0, 0, 0, 80));
        shadow->setOffset(0, 20);
        this->setGraphicsEffect(shadow);

        QLabel *iconLabel = new QLabel("🎓");
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setStyleSheet("font-size: 80px; background: transparent; color: #FFD700;");
        mainLayout->addWidget(iconLabel);

        mainLayout->addSpacing(15);

        QLabel *titleLabel = new QLabel("University");
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("color: #FFD700; font-size: 42px; font-weight: 300; letter-spacing: 8px; background: transparent; font-family: 'Georgia', serif;");
        mainLayout->addWidget(titleLabel);

        QLabel *subtitleLabel = new QLabel("Management System");
        subtitleLabel->setAlignment(Qt::AlignCenter);
        subtitleLabel->setStyleSheet("color: #C0C0D0; font-size: 18px; letter-spacing: 5px; background: transparent; font-family: 'Georgia', serif;");
        mainLayout->addWidget(subtitleLabel);

        mainLayout->addSpacing(40);

        QLabel *usernameLabel = new QLabel("👤 USERNAME");
        usernameLabel->setStyleSheet("color: #C0C0D0; font-size: 13px; font-weight: 600; letter-spacing: 3px;");
        mainLayout->addWidget(usernameLabel);

        usernameEdit = new QLineEdit();
        usernameEdit->setPlaceholderText("Enter your username");
        usernameEdit->setStyleSheet(R"(
            QLineEdit {
                background-color: rgba(20, 25, 45, 0.8);
                color: #FFFFFF;
                border: 1px solid rgba(255, 215, 0, 0.15);
                border-radius: 12px;
                padding: 18px 24px;
                font-size: 16px;
                min-height: 30px;
            }
            QLineEdit:focus {
                border-color: #FFD700;
                background-color: rgba(20, 25, 45, 0.95);
            }
            QLineEdit::placeholder {
                color: #606080;
                font-size: 15px;
            }
        )");
        mainLayout->addWidget(usernameEdit);

        mainLayout->addSpacing(25);

        QLabel *passwordLabel = new QLabel("🔒 PASSWORD");
        passwordLabel->setStyleSheet("color: #C0C0D0; font-size: 13px; font-weight: 600; letter-spacing: 3px;");
        mainLayout->addWidget(passwordLabel);

        passwordEdit = new QLineEdit();
        passwordEdit->setPlaceholderText("Enter your password");
        passwordEdit->setEchoMode(QLineEdit::Password);
        passwordEdit->setStyleSheet(R"(
            QLineEdit {
                background-color: rgba(20, 25, 45, 0.8);
                color: #FFFFFF;
                border: 1px solid rgba(255, 215, 0, 0.15);
                border-radius: 12px;
                padding: 18px 24px;
                font-size: 16px;
                min-height: 30px;
            }
            QLineEdit:focus {
                border-color: #FFD700;
                background-color: rgba(20, 25, 45, 0.95);
            }
            QLineEdit::placeholder {
                color: #606080;
                font-size: 15px;
            }
        )");
        mainLayout->addWidget(passwordEdit);

        mainLayout->addSpacing(35);

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(20);

        QPushButton *loginButton = new QPushButton("Sign In →");
        loginButton->setDefault(true);
        loginButton->setStyleSheet(R"(
            QPushButton {
                background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #FFD700, stop: 1 #F0C000);
                color: #1a1a2e;
                border: none;
                border-radius: 12px;
                padding: 18px 45px;
                font-weight: 700;
                font-size: 17px;
                letter-spacing: 2px;
                font-family: 'Georgia', serif;
            }
            QPushButton:hover {
                background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #F0C000, stop: 1 #D4A800);
            }
        )");
        loginButton->setMinimumWidth(180);

        QPushButton *cancelButton = new QPushButton("Cancel");
        cancelButton->setStyleSheet(R"(
            QPushButton {
                background: rgba(255, 255, 255, 0.05);
                color: #C0C0D0;
                border: 1px solid rgba(255, 215, 0, 0.15);
                border-radius: 12px;
                padding: 18px 45px;
                font-weight: 600;
                font-size: 16px;
                letter-spacing: 2px;
            }
            QPushButton:hover {
                background: rgba(255, 255, 255, 0.1);
                color: #FFFFFF;
            }
        )");
        cancelButton->setMinimumWidth(180);

        buttonLayout->addStretch();
        buttonLayout->addWidget(loginButton);
        buttonLayout->addWidget(cancelButton);
        buttonLayout->addStretch();

        mainLayout->addLayout(buttonLayout);
        mainLayout->addSpacing(25);

        QLabel *footerLabel = new QLabel("🏛️ University Management System v2.0");
        footerLabel->setAlignment(Qt::AlignCenter);
        footerLabel->setStyleSheet("color: #606080; font-size: 12px; letter-spacing: 2px; background: transparent;");
        mainLayout->addWidget(footerLabel);

        connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLogin);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
        connect(usernameEdit, &QLineEdit::returnPressed, this, &LoginDialog::onLogin);
        connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginDialog::onLogin);
    }

private slots:
    void onLogin() {
        QString username = usernameEdit->text().trimmed();
        QString password = passwordEdit->text().trimmed();

        if (username.isEmpty() || password.isEmpty()) {
            QMessageBox::warning(this, "Login Error", "❌ Please enter both username and password.");
            passwordEdit->clear();
            passwordEdit->setFocus();
            return;
        }

        loggedInUser = username;
        accept();
    }
};

// ============================================================
// MAIN APPLICATION
// ============================================================

class ModernUniversityGUI : public QMainWindow {
    Q_OBJECT

private:
    University *uni;
    QString currentUser;

    // ---------------------------------------------------------------
    // Local in-memory mirrors. These are the SINGLE SOURCE OF TRUTH for
    // everything the UI displays. Every add/remove/assign action updates
    // these first, then the visible tables are fully rebuilt from them.
    // This is what guarantees data survives page switches and that the
    // dashboard/statistics numbers are always correct.
    // ---------------------------------------------------------------
    QMap<QString, QStringList> dormitoryData;   // dorm name -> room numbers
    QStringList dormitoryNames;

    struct StudentInfo {
        int id;
        QString name;
        int year;
        QString dormitory; // "—" if unassigned
        QString room;      // "—" if unassigned
    };
    QList<StudentInfo> studentData;

    // Room capacity/occupancy, keyed by "DormName|RoomNumber"
    QMap<QString, int> roomCapacities;
    QMap<QString, int> roomOccupancy;

    struct RestaurantInfo {
        QString name;
        int capacity;
        QStringList breakfast;
        QStringList lunch;
        QStringList dinner;
    };
    QList<RestaurantInfo> restaurantData;

    // Navigation
    QWidget *centralWidget;
    QHBoxLayout *mainLayout;
    QWidget *sidebarWidget;
    QVBoxLayout *sidebarLayout;
    QStackedWidget *pagesStack;

    // Navigation buttons
    QPushButton *btnDashboard, *btnStudents, *btnDormitories, *btnRooms, *btnRestaurants, *btnStats, *btnSettings, *btnLogout;

    // Dashboard
    QLabel *welcomeLabel;
    QLabel *userNameLabel;      // sidebar user name
    QLabel *dashUserNameLabel;  // dashboard header user name (separate widget!)
    QLabel *totalStudentsLabel, *totalDormitoriesLabel, *totalRoomsLabel, *totalRestaurantsLabel;

    // Student Management
    QLineEdit *idInput, *nameInput, *yearInput;
    QComboBox *dormCombo;
    QComboBox *roomCombo; // optional specific room within the selected dormitory
    QTableWidget *studentTable;
    QTextEdit *output;

    // Dormitory Management
    QLineEdit *dormNameInput;
    QListWidget *dormList;

    // Room Management
    QComboBox *roomDormCombo;
    QLineEdit *roomNumberInput;
    QLineEdit *roomCapacityInput;
    QTableWidget *roomTable;

    // Restaurant Management
    QLineEdit *restaurantNameInput;
    QLineEdit *restaurantCapacityInput;
    QListWidget *restaurantList;
    QTableWidget *mealTable;
    QComboBox *mealTypeCombo;
    QLineEdit *mealItemInput;
    QPushButton *btnAddMeal;
    QPushButton *btnRemoveMeal;
    QString currentRestaurant;

    QStatusBar *statusBar;

public:
    ModernUniversityGUI(const QString &username, QWidget *parent = nullptr)
        : QMainWindow(parent), currentUser(username) {
        uni = new University();
        uni->loadAll();

        loadDataFromUniversity();
        setupUI();
        applyCustomStyle();
        refreshAllData();
    }

    ~ModernUniversityGUI() {
        delete uni;
    }

private:
    // ==================== SHARED CREATE/REMOVE HELPERS ====================
    // These are the ONLY places that create dormitories/rooms. Both the
    // startup seed data and the UI buttons go through them, so the local
    // mirrors and the real University object can never drift apart again.

    bool createDormitoryInternal(const QString &name) {
        if (dormitoryNames.contains(name)) return false;

        Restaurant defaultRestaurant("Breakfast: Eggs, Toast", "Lunch: Pasta, Salad", "Dinner: Steak, Vegetables");
        Dormitory newDorm(name.toStdString(), 50, defaultRestaurant);
        uni->addDormitory(newDorm); // actually register it, so assignment works later

        dormitoryNames.append(name);
        dormitoryData[name] = QStringList();
        return true;
    }

    // Creates the room in BOTH the local UI mirrors AND the real University
    // model, via University::addRoomToDormitory(). Previously this only
    // touched the local QMap/QMap mirrors, so `uni`/`Dormitory` never
    // actually had any rooms — which is the reason assignStudentToRoom()
    // always failed ("Dormitory may be full or not found"): the dormitory
    // had zero real Room objects to assign into.
    bool addRoomInternal(const QString &dormName, const QString &roomNumber, int capacity) {
        if (!dormitoryNames.contains(dormName)) return false;
        if (dormitoryData[dormName].contains(roomNumber)) return false;

        bool ok;
        int roomNum = roomNumber.toInt(&ok);
        if (!ok) return false;

        // Register the room in the real backend model first. If this fails
        // (e.g. duplicate room number the local mirror didn't know about),
        // bail out before touching the local mirrors so they can't drift.
        if (!uni->addRoomToDormitory(dormName.toStdString(), roomNum, capacity))
            return false;

        dormitoryData[dormName].append(roomNumber);
        QString key = dormName + "|" + roomNumber;
        roomCapacities[key] = capacity;
        roomOccupancy[key] = 0;
        return true;
    }

    void loadDataFromUniversity() {
        // Only seed demo data the very first time the app is run (i.e. when
        // there is nothing saved yet). Crucially, this now actually creates
        // the dormitories inside `uni` too — previously they only existed in
        // the UI lists, which is why assigning a student to "Dorm A" or
        // "Dorm B" always failed.
        if (dormitoryNames.isEmpty() && uni->getTotalDormitories() == 0) {
            createDormitoryInternal("Dorm A");
            createDormitoryInternal("Dorm B");
            addRoomInternal("Dorm A", "101", 2);
            addRoomInternal("Dorm A", "102", 2);
            addRoomInternal("Dorm B", "201", 2);
            addRoomInternal("Dorm B", "202", 2);
        }

        if (restaurantData.isEmpty()) {
            RestaurantInfo r1;
            r1.name = "Main Cafeteria";
            r1.capacity = 200;
            r1.breakfast << "Eggs" << "Toast" << "Coffee";
            r1.lunch << "Pasta" << "Salad" << "Juice";
            r1.dinner << "Steak" << "Vegetables" << "Water";
            restaurantData.append(r1);
        }
    }

    void saveDataToUniversity() {
        uni->saveAll();
    }

    void setupUI() {
        setWindowTitle(QString("🏛️ University Management System - %1").arg(currentUser));
        setMinimumSize(1400, 900);

        centralWidget = new UniversityBackground(this);
        setCentralWidget(centralWidget);

        mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        createSidebar();
        mainLayout->addWidget(sidebarWidget, 1);

        pagesStack = new QStackedWidget();
        pagesStack->setObjectName("pagesStack");
        pagesStack->setStyleSheet("background: transparent;");

        createDashboardPage();
        createStudentsPage();
        createDormitoriesPage();
        createRoomsPage();
        createRestaurantsPage();
        createStatsPage();
        createSettingsPage();

        mainLayout->addWidget(pagesStack, 5);

        statusBar = new QStatusBar(this);
        setStatusBar(statusBar);
        statusBar->showMessage(QString("🏛️ Welcome %1").arg(currentUser), 3000);
    }

    void createSidebar() {
        sidebarWidget = new QWidget();
        sidebarWidget->setObjectName("sidebar");
        sidebarWidget->setFixedWidth(260);

        sidebarLayout = new QVBoxLayout(sidebarWidget);
        sidebarLayout->setSpacing(2);
        sidebarLayout->setContentsMargins(15, 30, 15, 30);

        QLabel *logoLabel = new QLabel("🏛️ University");
        logoLabel->setObjectName("logoLabel");
        sidebarLayout->addWidget(logoLabel);

        QLabel *versionLabel = new QLabel("v2.0");
        versionLabel->setObjectName("versionLabel");
        sidebarLayout->addWidget(versionLabel);

        sidebarLayout->addSpacing(30);

        btnDashboard = createNavButton("📊 Dashboard", true);
        btnStudents = createNavButton("👨‍🎓 Students");
        btnDormitories = createNavButton("🏠 Dormitories");
        btnRooms = createNavButton("🚪 Rooms");
        btnRestaurants = createNavButton("🍽️ Restaurants");
        btnStats = createNavButton("📈 Statistics");
        btnSettings = createNavButton("⚙️ Settings");

        sidebarLayout->addWidget(btnDashboard);
        sidebarLayout->addWidget(btnStudents);
        sidebarLayout->addWidget(btnDormitories);
        sidebarLayout->addWidget(btnRooms);
        sidebarLayout->addWidget(btnRestaurants);
        sidebarLayout->addWidget(btnStats);
        sidebarLayout->addWidget(btnSettings);

        sidebarLayout->addSpacing(20);

        btnLogout = new QPushButton("🚪 Logout");
        btnLogout->setObjectName("logoutButton");
        btnLogout->setFixedHeight(45);
        sidebarLayout->addWidget(btnLogout);

        sidebarLayout->addStretch();

        QFrame *userFrame = new QFrame();
        userFrame->setObjectName("userFrame");
        QVBoxLayout *userLayout = new QVBoxLayout(userFrame);
        userLayout->setSpacing(4);

        QLabel *userIcon = new QLabel("👤");
        userIcon->setObjectName("userIcon");
        userNameLabel = new QLabel(currentUser);
        userNameLabel->setObjectName("userName");
        QLabel *userRole = new QLabel("Administrator");
        userRole->setObjectName("userRole");

        userLayout->addWidget(userIcon, 0, Qt::AlignCenter);
        userLayout->addWidget(userNameLabel, 0, Qt::AlignCenter);
        userLayout->addWidget(userRole, 0, Qt::AlignCenter);

        sidebarLayout->addWidget(userFrame);

        connect(btnDashboard, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(0); updateNavButtons(btnDashboard); });
        connect(btnStudents, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(1); updateNavButtons(btnStudents); refreshStudentTable(); refreshRoomComboForStudent(); });
        connect(btnDormitories, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(2); updateNavButtons(btnDormitories); refreshDormitoryList(); refreshDormCombo(); });
        connect(btnRooms, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(3); updateNavButtons(btnRooms); refreshRoomTable(); refreshRoomDormCombo(); });
        connect(btnRestaurants, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(4); updateNavButtons(btnRestaurants); refreshRestaurantList(); });
        connect(btnStats, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(5); updateNavButtons(btnStats); updateStatsPage(); });
        connect(btnSettings, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(6); updateNavButtons(btnSettings); });
        connect(btnLogout, &QPushButton::clicked, this, &ModernUniversityGUI::onLogout);
    }

    QPushButton* createNavButton(const QString &text, bool isActive = false) {
        QPushButton *btn = new QPushButton(text);
        btn->setObjectName("navButton");
        btn->setCheckable(true);
        btn->setChecked(isActive);
        btn->setFixedHeight(45);
        return btn;
    }

    void updateNavButtons(QPushButton *activeButton) {
        QList<QPushButton*> buttons = {btnDashboard, btnStudents, btnDormitories, btnRooms, btnRestaurants, btnStats, btnSettings};
        for (QPushButton *btn : buttons) {
            btn->setChecked(btn == activeButton);
        }
    }

    void createDashboardPage() {
        QWidget *page = new QWidget();
        page->setStyleSheet("background: transparent;");
        QVBoxLayout *layout = new QVBoxLayout(page);
        layout->setSpacing(25);
        layout->setContentsMargins(35, 35, 35, 35);

        QFrame *headerFrame = new QFrame();
        headerFrame->setObjectName("dashboardHeader");
        QVBoxLayout *headerLayout = new QVBoxLayout(headerFrame);

        welcomeLabel = new QLabel("Welcome back,");
        welcomeLabel->setObjectName("welcomeLabel");
        // IMPORTANT: this is a DIFFERENT label than the sidebar's userNameLabel.
        // Reusing the same member pointer here used to silently overwrite the
        // sidebar reference, which is why things looked inconsistent.
        dashUserNameLabel = new QLabel(currentUser);
        dashUserNameLabel->setObjectName("userNameLabel");

        headerLayout->addWidget(welcomeLabel);
        headerLayout->addWidget(dashUserNameLabel);
        layout->addWidget(headerFrame);

        QGridLayout *statsLayout = new QGridLayout();
        statsLayout->setSpacing(20);
        statsLayout->addWidget(createStatCard("👨‍🎓", "Students", &totalStudentsLabel), 0, 0);
        statsLayout->addWidget(createStatCard("🏠", "Dormitories", &totalDormitoriesLabel), 0, 1);
        statsLayout->addWidget(createStatCard("🚪", "Rooms", &totalRoomsLabel), 0, 2);
        statsLayout->addWidget(createStatCard("🍽️", "Restaurants", &totalRestaurantsLabel), 0, 3);
        layout->addLayout(statsLayout);

        QLabel *quickActionsLabel = new QLabel("Quick Actions");
        quickActionsLabel->setObjectName("quickActionsLabel");
        layout->addWidget(quickActionsLabel);

        QHBoxLayout *quickActionsLayout = new QHBoxLayout();
        quickActionsLayout->setSpacing(15);

        QPushButton *btnAddStudent = createQuickAction("➕ Add Student", "#FFD700");
        QPushButton *btnViewStudents = createQuickAction("👥 View Students", "#FFD700");
        QPushButton *btnAddDorm = createQuickAction("🏠 Add Dormitory", "#FFD700");
        QPushButton *btnSaveData = createQuickAction("💾 Save Data", "#FFD700");

        quickActionsLayout->addWidget(btnAddStudent);
        quickActionsLayout->addWidget(btnViewStudents);
        quickActionsLayout->addWidget(btnAddDorm);
        quickActionsLayout->addWidget(btnSaveData);
        quickActionsLayout->addStretch();
        layout->addLayout(quickActionsLayout);
        layout->addStretch();

        connect(btnAddStudent, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(1); updateNavButtons(btnStudents); });
        connect(btnViewStudents, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(1); updateNavButtons(btnStudents); refreshStudentTable(); });
        connect(btnAddDorm, &QPushButton::clicked, [this]() { pagesStack->setCurrentIndex(2); updateNavButtons(btnDormitories); });
        connect(btnSaveData, &QPushButton::clicked, [this]() {
            saveDataToUniversity();
            statusBar->showMessage("💾 Data saved!", 3000);
            addOutput("💾 Data saved successfully!", "#FFD700");
        });

        pagesStack->addWidget(page);
    }

    QFrame* createStatCard(const QString &icon, const QString &title, QLabel **valueLabel) {
        QFrame *card = new QFrame();
        card->setObjectName("statCard");
        QVBoxLayout *layout = new QVBoxLayout(card);
        layout->setSpacing(8);

        QLabel *iconLabel = new QLabel(icon);
        iconLabel->setObjectName("statIcon");

        QLabel *value = new QLabel("0");
        value->setObjectName("statValue");
        if (valueLabel) *valueLabel = value;

        QLabel *titleLabel = new QLabel(title);
        titleLabel->setObjectName("statTitle");

        layout->addWidget(iconLabel, 0, Qt::AlignCenter);
        layout->addWidget(value, 0, Qt::AlignCenter);
        layout->addWidget(titleLabel, 0, Qt::AlignCenter);
        return card;
    }

    void createStudentsPage() {
        QWidget *page = new QWidget();
        page->setStyleSheet("background: transparent;");
        QVBoxLayout *layout = new QVBoxLayout(page);
        layout->setSpacing(20);
        layout->setContentsMargins(30, 30, 30, 30);

        QLabel *titleLabel = new QLabel("👨‍🎓 Student Management");
        titleLabel->setObjectName("pageTitle");
        layout->addWidget(titleLabel);

        QGroupBox *inputGroup = new QGroupBox("Student Information");
        inputGroup->setObjectName("inputGroup");
        QGridLayout *gridLayout = new QGridLayout(inputGroup);
        gridLayout->setVerticalSpacing(12);
        gridLayout->setHorizontalSpacing(15);

        QLabel *idLabel = createLabel("🆔 ID");
        idInput = createLineEdit("Enter student ID");

        QLabel *nameLabel = createLabel("👤 Name");
        nameInput = createLineEdit("Enter student name");

        QLabel *yearLabel = createLabel("📅 Year");
        yearInput = createLineEdit("Enter academic year (1-5)");

        QLabel *dormLabel = createLabel("🏠 Dormitory");
        dormCombo = new QComboBox();
        dormCombo->setObjectName("inputField");

        QLabel *roomLabel = createLabel("🚪 Room (optional)");
        roomCombo = new QComboBox();
        roomCombo->setObjectName("inputField");

        gridLayout->addWidget(idLabel, 0, 0);
        gridLayout->addWidget(idInput, 0, 1);
        gridLayout->addWidget(nameLabel, 1, 0);
        gridLayout->addWidget(nameInput, 1, 1);
        gridLayout->addWidget(yearLabel, 2, 0);
        gridLayout->addWidget(yearInput, 2, 1);
        gridLayout->addWidget(dormLabel, 3, 0);
        gridLayout->addWidget(dormCombo, 3, 1);
        gridLayout->addWidget(roomLabel, 4, 0);
        gridLayout->addWidget(roomCombo, 4, 1);

        refreshDormCombo();          // also populates roomCombo via the dorm change handler
        refreshRoomComboForStudent();

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(10);

        QPushButton *btnAdd = createActionButton("➕ Add", "#FFD700");
        QPushButton *btnRemove = createActionButton("➖ Remove", "#E74C3C");
        QPushButton *btnAssign = createActionButton("📌 Assign", "#FFD700");
        QPushButton *btnClear = createActionButton("🗑️ Clear", "#95A5A6");

        buttonLayout->addWidget(btnAdd);
        buttonLayout->addWidget(btnRemove);
        buttonLayout->addWidget(btnAssign);
        buttonLayout->addWidget(btnClear);
        buttonLayout->addStretch();

        QVBoxLayout *inputLayout = new QVBoxLayout();
        inputLayout->addWidget(inputGroup);
        inputLayout->addLayout(buttonLayout);
        layout->addLayout(inputLayout);

        QLabel *tableLabel = new QLabel("📋 Student List");
        tableLabel->setObjectName("tableLabel");
        layout->addWidget(tableLabel);

        studentTable = new QTableWidget();
        studentTable->setObjectName("studentTable");
        studentTable->setColumnCount(5);
        studentTable->setHorizontalHeaderLabels({"ID", "Name", "Year", "Dormitory", "Room"});
        studentTable->horizontalHeader()->setStretchLastSection(true);
        studentTable->setAlternatingRowColors(true);
        studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        layout->addWidget(studentTable);

        output = new QTextEdit();
        output->setObjectName("output");
        output->setReadOnly(true);
        output->setMaximumHeight(100);
        output->setFont(QFont("Consolas", 10));
        layout->addWidget(output);

        connect(btnAdd, &QPushButton::clicked, this, &ModernUniversityGUI::onAddStudent);
        connect(btnRemove, &QPushButton::clicked, this, &ModernUniversityGUI::onRemoveStudent);
        connect(btnAssign, &QPushButton::clicked, this, &ModernUniversityGUI::onAssignStudent);
        connect(btnClear, &QPushButton::clicked, this, &ModernUniversityGUI::onClearAll);
        connect(dormCombo, &QComboBox::currentTextChanged, [this](const QString &) { refreshRoomComboForStudent(); });

        pagesStack->addWidget(page);
    }

    void createDormitoriesPage() {
        QWidget *page = new QWidget();
        page->setStyleSheet("background: transparent;");
        QVBoxLayout *layout = new QVBoxLayout(page);
        layout->setSpacing(20);
        layout->setContentsMargins(30, 30, 30, 30);

        QLabel *titleLabel = new QLabel("🏠 Dormitory Management");
        titleLabel->setObjectName("pageTitle");
        layout->addWidget(titleLabel);

        QHBoxLayout *contentLayout = new QHBoxLayout();
        contentLayout->setSpacing(25);

        QWidget *leftPanel = new QWidget();
        QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

        QGroupBox *addGroup = new QGroupBox("Add Dormitory");
        addGroup->setObjectName("inputGroup");
        QVBoxLayout *addLayout = new QVBoxLayout(addGroup);

        dormNameInput = createLineEdit("Enter dormitory name");
        addLayout->addWidget(dormNameInput);

        QPushButton *btnAddDorm = createActionButton("➕ Add Dormitory", "#FFD700");
        addLayout->addWidget(btnAddDorm);

        leftLayout->addWidget(addGroup);
        leftLayout->addStretch();
        contentLayout->addWidget(leftPanel, 1);

        QWidget *rightPanel = new QWidget();
        QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

        QLabel *listLabel = new QLabel("📋 Dormitory List");
        listLabel->setObjectName("tableLabel");
        rightLayout->addWidget(listLabel);

        dormList = new QListWidget();
        dormList->setObjectName("studentTable");
        rightLayout->addWidget(dormList);

        QHBoxLayout *dormButtonLayout = new QHBoxLayout();
        QPushButton *btnRemoveDorm = createActionButton("➖ Remove", "#E74C3C");
        QPushButton *btnRefreshDorm = createActionButton("🔄 Refresh", "#FFD700");
        dormButtonLayout->addWidget(btnRemoveDorm);
        dormButtonLayout->addWidget(btnRefreshDorm);
        dormButtonLayout->addStretch();
        rightLayout->addLayout(dormButtonLayout);

        contentLayout->addWidget(rightPanel, 2);
        layout->addLayout(contentLayout);

        connect(btnAddDorm, &QPushButton::clicked, this, &ModernUniversityGUI::onAddDormitory);
        connect(btnRemoveDorm, &QPushButton::clicked, this, &ModernUniversityGUI::onRemoveDormitory);
        connect(btnRefreshDorm, &QPushButton::clicked, [this]() {
            refreshDormitoryList();
            refreshDormCombo();
            refreshRoomDormCombo();
        });

        pagesStack->addWidget(page);
    }

    void createRoomsPage() {
        QWidget *page = new QWidget();
        page->setStyleSheet("background: transparent;");
        QVBoxLayout *layout = new QVBoxLayout(page);
        layout->setSpacing(20);
        layout->setContentsMargins(30, 30, 30, 30);

        QLabel *titleLabel = new QLabel("🚪 Room Management");
        titleLabel->setObjectName("pageTitle");
        layout->addWidget(titleLabel);

        QHBoxLayout *contentLayout = new QHBoxLayout();
        contentLayout->setSpacing(25);

        QWidget *leftPanel = new QWidget();
        QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

        QGroupBox *addGroup = new QGroupBox("Add Room");
        addGroup->setObjectName("inputGroup");
        QVBoxLayout *addLayout = new QVBoxLayout(addGroup);

        QLabel *dormSelectLabel = createLabel("🏠 Select Dormitory");
        addLayout->addWidget(dormSelectLabel);

        roomDormCombo = new QComboBox();
        roomDormCombo->setObjectName("inputField");
        refreshRoomDormCombo();
        addLayout->addWidget(roomDormCombo);

        QLabel *roomNumLabel = createLabel("🔢 Room Number");
        addLayout->addWidget(roomNumLabel);

        roomNumberInput = createLineEdit("Enter room number");
        addLayout->addWidget(roomNumberInput);

        QLabel *roomCapLabel = createLabel("👥 Capacity");
        addLayout->addWidget(roomCapLabel);

        roomCapacityInput = createLineEdit("Max students in this room");
        roomCapacityInput->setText("2");
        addLayout->addWidget(roomCapacityInput);

        QPushButton *btnAddRoom = createActionButton("➕ Add Room", "#FFD700");
        addLayout->addWidget(btnAddRoom);

        leftLayout->addWidget(addGroup);
        leftLayout->addStretch();
        contentLayout->addWidget(leftPanel, 1);

        QWidget *rightPanel = new QWidget();
        QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

        QLabel *listLabel = new QLabel("📋 Room List");
        listLabel->setObjectName("tableLabel");
        rightLayout->addWidget(listLabel);

        roomTable = new QTableWidget();
        roomTable->setObjectName("studentTable");
        roomTable->setColumnCount(4);
        roomTable->setHorizontalHeaderLabels({"Room Number", "Dormitory", "Occupancy", "Status"});
        roomTable->horizontalHeader()->setStretchLastSection(true);
        roomTable->setAlternatingRowColors(true);
        rightLayout->addWidget(roomTable);

        QHBoxLayout *roomButtonLayout = new QHBoxLayout();
        QPushButton *btnRemoveRoom = createActionButton("➖ Remove", "#E74C3C");
        QPushButton *btnRefreshRoom = createActionButton("🔄 Refresh", "#FFD700");
        roomButtonLayout->addWidget(btnRemoveRoom);
        roomButtonLayout->addWidget(btnRefreshRoom);
        roomButtonLayout->addStretch();
        rightLayout->addLayout(roomButtonLayout);

        contentLayout->addWidget(rightPanel, 2);
        layout->addLayout(contentLayout);

        connect(btnAddRoom, &QPushButton::clicked, this, &ModernUniversityGUI::onAddRoom);
        connect(btnRemoveRoom, &QPushButton::clicked, this, &ModernUniversityGUI::onRemoveRoom);
        connect(btnRefreshRoom, &QPushButton::clicked, [this]() {
            refreshRoomTable();
            refreshRoomDormCombo();
        });

        pagesStack->addWidget(page);
    }

    void createRestaurantsPage() {
        QWidget *page = new QWidget();
        page->setStyleSheet("background: transparent;");
        QVBoxLayout *layout = new QVBoxLayout(page);
        layout->setSpacing(20);
        layout->setContentsMargins(30, 30, 30, 30);

        QLabel *titleLabel = new QLabel("🍽️ Restaurant Management");
        titleLabel->setObjectName("pageTitle");
        layout->addWidget(titleLabel);

        QHBoxLayout *contentLayout = new QHBoxLayout();
        contentLayout->setSpacing(25);

        QWidget *leftPanel = new QWidget();
        QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

        QGroupBox *addGroup = new QGroupBox("Add Restaurant");
        addGroup->setObjectName("inputGroup");
        QVBoxLayout *addLayout = new QVBoxLayout(addGroup);

        restaurantNameInput = createLineEdit("Enter restaurant name");
        addLayout->addWidget(restaurantNameInput);

        restaurantCapacityInput = createLineEdit("Enter capacity");
        addLayout->addWidget(restaurantCapacityInput);

        QPushButton *btnAddRestaurant = createActionButton("➕ Add Restaurant", "#FFD700");
        addLayout->addWidget(btnAddRestaurant);

        leftLayout->addWidget(addGroup);

        QGroupBox *mealGroup = new QGroupBox("🍽️ Manage Meals");
        mealGroup->setObjectName("inputGroup");
        QVBoxLayout *mealLayout = new QVBoxLayout(mealGroup);

        mealTypeCombo = new QComboBox();
        mealTypeCombo->setObjectName("inputField");
        mealTypeCombo->addItems({"🌅 Breakfast", "☀️ Lunch", "🌙 Dinner"});
        mealLayout->addWidget(mealTypeCombo);

        mealItemInput = createLineEdit("Enter meal item");
        mealLayout->addWidget(mealItemInput);

        QHBoxLayout *mealButtonLayout = new QHBoxLayout();
        btnAddMeal = createActionButton("➕ Add Meal", "#FFD700");
        btnRemoveMeal = createActionButton("➖ Remove Meal", "#E74C3C");
        mealButtonLayout->addWidget(btnAddMeal);
        mealButtonLayout->addWidget(btnRemoveMeal);
        mealButtonLayout->addStretch();
        mealLayout->addLayout(mealButtonLayout);

        leftLayout->addWidget(mealGroup);
        leftLayout->addStretch();
        contentLayout->addWidget(leftPanel, 1);

        QWidget *rightPanel = new QWidget();
        QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

        QLabel *listLabel = new QLabel("📋 Restaurant List");
        listLabel->setObjectName("tableLabel");
        rightLayout->addWidget(listLabel);

        restaurantList = new QListWidget();
        restaurantList->setObjectName("studentTable");
        rightLayout->addWidget(restaurantList);

        QHBoxLayout *restButtonLayout = new QHBoxLayout();
        QPushButton *btnRemoveRestaurant = createActionButton("➖ Remove", "#E74C3C");
        QPushButton *btnRefreshRest = createActionButton("🔄 Refresh", "#FFD700");
        restButtonLayout->addWidget(btnRemoveRestaurant);
        restButtonLayout->addWidget(btnRefreshRest);
        restButtonLayout->addStretch();
        rightLayout->addLayout(restButtonLayout);

        QLabel *mealTableLabel = new QLabel("📋 Meal Menu");
        mealTableLabel->setObjectName("tableLabel");
        rightLayout->addWidget(mealTableLabel);

        mealTable = new QTableWidget();
        mealTable->setObjectName("studentTable");
        mealTable->setColumnCount(2);
        mealTable->setHorizontalHeaderLabels({"Meal Type", "Items"});
        mealTable->horizontalHeader()->setStretchLastSection(true);
        mealTable->setAlternatingRowColors(true);
        mealTable->setMinimumHeight(150);
        rightLayout->addWidget(mealTable);

        contentLayout->addWidget(rightPanel, 2);
        layout->addLayout(contentLayout);

        connect(btnAddRestaurant, &QPushButton::clicked, this, &ModernUniversityGUI::onAddRestaurant);
        connect(btnRemoveRestaurant, &QPushButton::clicked, this, &ModernUniversityGUI::onRemoveRestaurant);
        connect(btnRefreshRest, &QPushButton::clicked, [this]() { refreshRestaurantList(); });
        connect(btnAddMeal, &QPushButton::clicked, this, &ModernUniversityGUI::onAddMeal);
        connect(btnRemoveMeal, &QPushButton::clicked, this, &ModernUniversityGUI::onRemoveMeal);
        connect(restaurantList, &QListWidget::itemClicked, this, &ModernUniversityGUI::onRestaurantSelected);

        pagesStack->addWidget(page);
    }

    void createStatsPage() {
        QWidget *page = new QWidget();
        page->setStyleSheet("background: transparent;");
        QVBoxLayout *layout = new QVBoxLayout(page);
        layout->setSpacing(25);
        layout->setContentsMargins(35, 35, 35, 35);

        QLabel *titleLabel = new QLabel("📈 Statistics");
        titleLabel->setObjectName("pageTitle");
        layout->addWidget(titleLabel);

        QFrame *statsFrame = new QFrame();
        statsFrame->setObjectName("statsFrame");
        QGridLayout *statsGrid = new QGridLayout(statsFrame);
        statsGrid->setSpacing(25);

        QStringList icons = {"👨‍🎓", "🏠", "🚪", "🍽️"};
        QStringList labels = {"Total Students", "Dormitories", "Rooms", "Restaurants"};

        for (int i = 0; i < 4; i++) {
            QFrame *statItem = new QFrame();
            statItem->setObjectName("statItem");
            QVBoxLayout *itemLayout = new QVBoxLayout(statItem);

            QLabel *icon = new QLabel(icons[i]);
            icon->setObjectName("statItemIcon");
            QLabel *value = new QLabel("0");
            value->setObjectName("statItemValue");
            value->setProperty("statIndex", i);
            QLabel *label = new QLabel(labels[i]);
            label->setObjectName("statItemLabel");

            itemLayout->addWidget(icon, 0, Qt::AlignCenter);
            itemLayout->addWidget(value, 0, Qt::AlignCenter);
            itemLayout->addWidget(label, 0, Qt::AlignCenter);
            statsGrid->addWidget(statItem, i/2, i%2);
        }

        layout->addWidget(statsFrame);
        layout->addStretch();
        pagesStack->addWidget(page);
    }

    void createSettingsPage() {
        QWidget *page = new QWidget();
        page->setStyleSheet("background: transparent;");
        QVBoxLayout *layout = new QVBoxLayout(page);
        layout->setSpacing(25);
        layout->setContentsMargins(35, 35, 35, 35);

        QLabel *titleLabel = new QLabel("⚙️ Settings");
        titleLabel->setObjectName("pageTitle");
        layout->addWidget(titleLabel);

        QGroupBox *userGroup = new QGroupBox("👤 User Information");
        userGroup->setObjectName("settingsGroup");
        QVBoxLayout *userLayout = new QVBoxLayout(userGroup);

        QLabel *userInfoLabel = new QLabel(QString("👤 Logged in as: <b>%1</b>").arg(currentUser));
        userInfoLabel->setObjectName("userInfoLabel");
        userLayout->addWidget(userInfoLabel);

        QLabel *userRoleLabel = new QLabel("🔑 Role: Administrator");
        userRoleLabel->setObjectName("userInfoLabel");
        userLayout->addWidget(userRoleLabel);
        layout->addWidget(userGroup);

        QGroupBox *settingsGroup = new QGroupBox("⚙️ Application Settings");
        settingsGroup->setObjectName("settingsGroup");
        QVBoxLayout *settingsLayout = new QVBoxLayout(settingsGroup);

        QPushButton *btnRefresh = new QPushButton("🔄 Refresh Data");
        btnRefresh->setObjectName("settingsButton");
        QPushButton *btnExport = new QPushButton("📤 Export Data");
        btnExport->setObjectName("settingsButton");
        QPushButton *btnImport = new QPushButton("📥 Import Data");
        btnImport->setObjectName("settingsButton");
        QPushButton *btnClearAll = new QPushButton("🗑️ Clear All Data");
        btnClearAll->setObjectName("settingsButton");

        settingsLayout->addWidget(btnRefresh);
        settingsLayout->addWidget(btnExport);
        settingsLayout->addWidget(btnImport);
        settingsLayout->addWidget(btnClearAll);
        settingsLayout->addStretch();
        layout->addWidget(settingsGroup);

        connect(btnRefresh, &QPushButton::clicked, [this]() {
            refreshAllData();
            statusBar->showMessage("🔄 Data refreshed!", 3000);
            addOutput("🔄 Data refreshed!", "#FFD700");
        });

        connect(btnClearAll, &QPushButton::clicked, [this]() {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Clear Data",
                                                                      "⚠️ This will clear all data. Are you sure?",
                                                                      QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                dormitoryData.clear();
                dormitoryNames.clear();
                restaurantData.clear();
                studentData.clear();
                roomCapacities.clear();
                roomOccupancy.clear();
                refreshAllData();
                addOutput("🗑️ All data cleared", "#E74C3C");
            }
        });

        pagesStack->addWidget(page);
    }

    // ==================== DATA REFRESH METHODS ====================

    void refreshAllData() {
        refreshStudentTable();
        refreshDormitoryList();
        refreshRoomTable();
        refreshRestaurantList();
        refreshDormCombo();
        refreshRoomDormCombo();
        refreshRoomComboForStudent();
        updateDashboardStats();
        updateStatsPage();
    }

    // Local mirrors (studentData / dormitoryNames / dormitoryData / restaurantData)
    // are the source of truth here, so these numbers are always correct,
    // regardless of what University internally tracks.
    void updateDashboardStats() {
        if (totalStudentsLabel) totalStudentsLabel->setText(QString::number(studentData.size()));
        if (totalDormitoriesLabel) totalDormitoriesLabel->setText(QString::number(dormitoryNames.size()));

        int totalRooms = 0;
        for (const QStringList &rooms : dormitoryData.values()) {
            totalRooms += rooms.size();
        }
        if (totalRoomsLabel) totalRoomsLabel->setText(QString::number(totalRooms));
        if (totalRestaurantsLabel) totalRestaurantsLabel->setText(QString::number(restaurantData.size()));
    }

    // Fully rebuilds the student table from studentData every time it's
    // called. This is what fixes "student disappears when I switch pages":
    // the table is no longer the source of truth, studentData is, and it is
    // never touched by navigation - only by add/remove/assign actions.
    void refreshStudentTable() {
        if (!studentTable) return;
        studentTable->setRowCount(0);
        for (const StudentInfo &s : studentData) {
            int row = studentTable->rowCount();
            studentTable->insertRow(row);
            studentTable->setItem(row, 0, new QTableWidgetItem(QString::number(s.id)));
            studentTable->setItem(row, 1, new QTableWidgetItem(s.name));
            studentTable->setItem(row, 2, new QTableWidgetItem(QString::number(s.year)));
            studentTable->setItem(row, 3, new QTableWidgetItem(s.dormitory));
            studentTable->setItem(row, 4, new QTableWidgetItem(s.room));
        }
        updateDashboardStats();
    }

    void refreshDormitoryList() {
        if (!dormList) return;
        dormList->clear();
        for (const QString &dorm : dormitoryNames) {
            int roomCount = dormitoryData[dorm].size();
            dormList->addItem(QString("%1 🏠 %2 rooms").arg(dorm).arg(roomCount));
        }
        updateDashboardStats();
    }

    // Shows real occupancy/capacity per room, so over-capacity assignment
    // is visible immediately instead of silently allowed.
    void refreshRoomTable() {
        if (!roomTable) return;
        roomTable->setRowCount(0);
        for (const QString &dorm : dormitoryNames) {
            for (const QString &room : dormitoryData[dorm]) {
                QString key = dorm + "|" + room;
                int cap = roomCapacities.value(key, 2);
                int occ = roomOccupancy.value(key, 0);

                int row = roomTable->rowCount();
                roomTable->insertRow(row);
                roomTable->setItem(row, 0, new QTableWidgetItem(room));
                roomTable->setItem(row, 1, new QTableWidgetItem(dorm));
                roomTable->setItem(row, 2, new QTableWidgetItem(QString("%1 / %2").arg(occ).arg(cap)));
                roomTable->setItem(row, 3, new QTableWidgetItem(occ >= cap ? "🔴 Full" : "🟢 Available"));
            }
        }
        updateDashboardStats();
    }

    void refreshRestaurantList() {
        if (!restaurantList) return;
        restaurantList->clear();
        for (const RestaurantInfo &rest : restaurantData) {
            restaurantList->addItem(QString("%1 🍽️ %2").arg(rest.name).arg(rest.capacity));
        }
        updateDashboardStats();
        if (!restaurantData.isEmpty()) {
            currentRestaurant = restaurantData[0].name;
            displayMeals(0);
        }
    }

    void displayMeals(int index) {
        if (!mealTable || index < 0 || index >= restaurantData.size()) return;

        const RestaurantInfo &rest = restaurantData[index];
        mealTable->setRowCount(0);

        int row = mealTable->rowCount();
        mealTable->insertRow(row);
        mealTable->setItem(row, 0, new QTableWidgetItem("🌅 Breakfast"));
        mealTable->setItem(row, 1, new QTableWidgetItem(rest.breakfast.join(", ")));

        row = mealTable->rowCount();
        mealTable->insertRow(row);
        mealTable->setItem(row, 0, new QTableWidgetItem("☀️ Lunch"));
        mealTable->setItem(row, 1, new QTableWidgetItem(rest.lunch.join(", ")));

        row = mealTable->rowCount();
        mealTable->insertRow(row);
        mealTable->setItem(row, 0, new QTableWidgetItem("🌙 Dinner"));
        mealTable->setItem(row, 1, new QTableWidgetItem(rest.dinner.join(", ")));
    }

    void refreshDormCombo(QComboBox *combo = nullptr) {
        if (!combo) combo = dormCombo;
        if (!combo) return;
        QString previous = combo->currentText();
        combo->clear();
        combo->addItem("— None");
        for (const QString &dorm : dormitoryNames) {
            combo->addItem(dorm);
        }
        int idx = combo->findText(previous);
        if (idx >= 0) combo->setCurrentIndex(idx);

        if (combo == dormCombo) {
            refreshRoomComboForStudent();
        }
    }

    void refreshRoomDormCombo() {
        if (!roomDormCombo) return;
        roomDormCombo->clear();
        roomDormCombo->addItem("— None");
        for (const QString &dorm : dormitoryNames) {
            roomDormCombo->addItem(dorm);
        }
    }

    // Populates the "Room (optional)" combo on the Students page based on
    // whichever dormitory is currently selected, showing live occupancy so
    // it's clear which rooms are already full.
    void refreshRoomComboForStudent() {
        if (!roomCombo || !dormCombo) return;
        QString dorm = dormCombo->currentText();
        roomCombo->clear();
        roomCombo->addItem("— None", QString());

        if (dorm == "— None" || !dormitoryData.contains(dorm)) return;

        for (const QString &room : dormitoryData[dorm]) {
            QString key = dorm + "|" + room;
            int cap = roomCapacities.value(key, 2);
            int occ = roomOccupancy.value(key, 0);
            QString label = QString("%1 (%2/%3)%4").arg(room).arg(occ).arg(cap)
                                .arg(occ >= cap ? "  🔴 FULL" : "");
            roomCombo->addItem(label, room); // store the real room number as item data
        }
    }

    void updateStatsPage() {
        QList<QLabel*> statValues = findChildren<QLabel*>("statItemValue");
        if (statValues.size() >= 4) {
            statValues[0]->setText(QString::number(studentData.size()));
            statValues[1]->setText(QString::number(dormitoryNames.size()));
            int totalRooms = 0;
            for (const QStringList &rooms : dormitoryData.values()) {
                totalRooms += rooms.size();
            }
            statValues[2]->setText(QString::number(totalRooms));
            statValues[3]->setText(QString::number(restaurantData.size()));
        }
    }

    // ==================== HELPER METHODS ====================

    QLabel* createLabel(const QString &text) {
        QLabel *label = new QLabel(text);
        label->setObjectName("inputLabel");
        return label;
    }

    QLineEdit* createLineEdit(const QString &placeholder) {
        QLineEdit *edit = new QLineEdit();
        edit->setPlaceholderText(placeholder);
        edit->setObjectName("inputField");
        return edit;
    }

    QPushButton* createActionButton(const QString &text, const QString &color) {
        QPushButton *btn = new QPushButton(text);
        btn->setObjectName("actionButton");
        btn->setStyleSheet(QString(R"(
            QPushButton {
                background-color: %1;
                color: #1a1a2e;
                border: none;
                border-radius: 8px;
                padding: 10px 20px;
                font-weight: 700;
                font-size: 13px;
                letter-spacing: 0.5px;
            }
            QPushButton:hover {
                background-color: %1;
                opacity: 0.8;
            }
        )").arg(color));
        return btn;
    }

    QPushButton* createQuickAction(const QString &text, const QString &color) {
        QPushButton *btn = new QPushButton(text);
        btn->setObjectName("quickAction");
        btn->setStyleSheet(QString(R"(
            QPushButton {
                background-color: %1;
                color: #1a1a2e;
                border: none;
                border-radius: 10px;
                padding: 14px 25px;
                font-weight: 700;
                font-size: 14px;
                letter-spacing: 0.5px;
            }
            QPushButton:hover {
                background-color: %1;
                opacity: 0.8;
            }
        )").arg(color));
        return btn;
    }

    void applyCustomStyle() {
        setStyleSheet(R"(
            QMainWindow { background: transparent; }

            QWidget {
                font-family: 'Segoe UI', -apple-system, BlinkMacSystemFont, sans-serif;
                font-size: 13px;
                color: #E0E0E0;
            }

            #sidebar {
                background: rgba(10, 15, 30, 0.95);
                border-right: 1px solid rgba(255, 215, 0, 0.1);
            }

            #logoLabel {
                color: #FFD700;
                font-size: 24px;
                font-weight: 300;
                letter-spacing: 3px;
                padding: 5px 0;
            }

            #versionLabel {
                color: #8080A0;
                font-size: 11px;
                letter-spacing: 2px;
                padding-bottom: 10px;
                border-bottom: 1px solid rgba(255, 215, 0, 0.08);
            }

            #navButton {
                background: transparent;
                color: #A0A0C0;
                border: none;
                border-radius: 8px;
                padding: 10px 16px;
                font-size: 14px;
                text-align: left;
                font-weight: 400;
                letter-spacing: 0.5px;
            }

            #navButton:hover {
                background: rgba(255, 215, 0, 0.08);
                color: #FFFFFF;
            }

            #navButton:checked {
                background: rgba(255, 215, 0, 0.12);
                color: #FFD700;
                font-weight: 500;
                border-left: 3px solid #FFD700;
            }

            #logoutButton {
                background: rgba(255, 215, 0, 0.08);
                color: #FFD700;
                border: 1px solid rgba(255, 215, 0, 0.15);
                border-radius: 8px;
                padding: 10px 16px;
                font-weight: 500;
                font-size: 14px;
                letter-spacing: 0.5px;
            }

            #logoutButton:hover {
                background: rgba(255, 215, 0, 0.15);
                border-color: #FFD700;
            }

            #userFrame {
                background: rgba(255, 255, 255, 0.03);
                border-radius: 10px;
                padding: 12px;
                border: 1px solid rgba(255, 215, 0, 0.08);
            }

            #userIcon {
                font-size: 28px;
                color: #FFD700;
            }

            #userName {
                color: #FFFFFF;
                font-size: 14px;
                font-weight: 500;
            }

            #userRole {
                color: #8080A0;
                font-size: 11px;
                letter-spacing: 1px;
            }

            #dashboardHeader {
                background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,
                    stop: 0 rgba(255, 215, 0, 0.06), stop: 1 rgba(255, 215, 0, 0.02));
                border: 1px solid rgba(255, 215, 0, 0.08);
                border-radius: 16px;
                padding: 25px;
                background-color: rgba(10, 15, 30, 0.5);
            }

            #welcomeLabel {
                color: #A0A0C0;
                font-size: 16px;
                font-weight: 300;
                letter-spacing: 1px;
            }

            #userNameLabel {
                color: #FFD700;
                font-size: 32px;
                font-weight: 300;
                letter-spacing: 2px;
            }

            #statCard {
                background: rgba(10, 15, 30, 0.6);
                border: 1px solid rgba(255, 215, 0, 0.08);
                border-radius: 14px;
                padding: 20px;
                min-height: 110px;
            }

            #statCard:hover {
                border-color: rgba(255, 215, 0, 0.2);
                background: rgba(10, 15, 30, 0.8);
            }

            #statIcon {
                font-size: 28px;
            }

            #statValue {
                color: #FFD700;
                font-size: 30px;
                font-weight: 300;
                letter-spacing: 1px;
            }

            #statTitle {
                color: #A0A0C0;
                font-size: 13px;
                letter-spacing: 1px;
                font-weight: 400;
            }

            #quickActionsLabel {
                color: #FFFFFF;
                font-size: 18px;
                font-weight: 300;
                letter-spacing: 2px;
                margin-top: 15px;
            }

            #quickAction {
                font-size: 13px;
                padding: 12px 22px;
                letter-spacing: 0.5px;
                font-weight: 500;
            }

            #pageTitle {
                color: #FFD700;
                font-size: 26px;
                font-weight: 300;
                letter-spacing: 2px;
                padding: 10px 0;
                border-bottom: 1px solid rgba(255, 215, 0, 0.08);
            }

            #inputGroup {
                color: #E0E0E0;
                font-weight: 400;
                font-size: 13px;
                border: 1px solid rgba(255, 215, 0, 0.08);
                border-radius: 12px;
                padding: 20px;
                background-color: rgba(10, 15, 30, 0.5);
            }

            #inputGroup::title {
                color: #A0A0C0;
                letter-spacing: 1px;
            }

            #inputLabel {
                color: #A0A0C0;
                font-weight: 500;
                font-size: 12px;
                letter-spacing: 1px;
            }

            #inputField, QComboBox, QSpinBox {
                background-color: rgba(20, 25, 45, 0.8);
                color: #FFFFFF;
                border: 1px solid rgba(255, 215, 0, 0.1);
                border-radius: 8px;
                padding: 10px 14px;
                font-size: 13px;
            }

            #inputField:focus, QComboBox:focus, QSpinBox:focus {
                border-color: #FFD700;
                background-color: rgba(20, 25, 45, 0.95);
            }

            QComboBox::drop-down {
                border: none;
                padding-right: 10px;
            }

            QComboBox QAbstractItemView {
                background-color: #1a1f2f;
                color: #FFFFFF;
                selection-background-color: rgba(255, 215, 0, 0.2);
                selection-color: #FFFFFF;
                border: 1px solid rgba(255, 215, 0, 0.1);
            }

            #studentTable, QListWidget {
                background-color: rgba(10, 15, 30, 0.7);
                color: #E0E0E0;
                border: 1px solid rgba(255, 215, 0, 0.08);
                border-radius: 10px;
                gridline-color: rgba(255, 215, 0, 0.05);
            }

            #studentTable::item:selected, QListWidget::item:selected {
                background-color: rgba(255, 215, 0, 0.12);
                color: #FFD700;
            }

            #studentTable::item:hover, QListWidget::item:hover {
                background-color: rgba(255, 255, 255, 0.03);
            }

            #tableLabel {
                color: #A0A0C0;
                font-size: 14px;
                font-weight: 400;
                letter-spacing: 1px;
            }

            #output {
                background-color: rgba(10, 15, 30, 0.7);
                color: #E0E0E0;
                border: 1px solid rgba(255, 215, 0, 0.08);
                border-radius: 10px;
                padding: 12px;
                font-size: 12px;
                line-height: 1.6;
                font-family: 'Consolas', monospace;
            }

            #actionButton {
                font-size: 12px;
                padding: 8px 18px;
                letter-spacing: 0.5px;
                font-weight: 500;
            }

            #settingsGroup {
                color: #E0E0E0;
                border: 1px solid rgba(255, 215, 0, 0.08);
                border-radius: 12px;
                padding: 20px;
                background-color: rgba(10, 15, 30, 0.5);
            }

            #settingsGroup::title {
                color: #A0A0C0;
                letter-spacing: 1px;
            }

            #settingsButton {
                background-color: rgba(10, 15, 30, 0.6);
                color: #C0C0D0;
                border: 1px solid rgba(255, 215, 0, 0.08);
                border-radius: 8px;
                padding: 12px 20px;
                font-size: 13px;
                text-align: left;
                margin: 5px 0;
                letter-spacing: 0.5px;
            }

            #settingsButton:hover {
                background-color: rgba(10, 15, 30, 0.9);
                border-color: rgba(255, 215, 0, 0.2);
                color: #FFFFFF;
            }

            #userInfoLabel {
                color: #E0E0E0;
                font-size: 14px;
                padding: 5px 0;
                letter-spacing: 0.5px;
            }

            #statsFrame {
                background: rgba(10, 15, 30, 0.5);
                border-radius: 14px;
                padding: 25px;
                border: 1px solid rgba(255, 215, 0, 0.08);
            }

            #statItem {
                background: rgba(10, 15, 30, 0.6);
                border: 1px solid rgba(255, 215, 0, 0.08);
                border-radius: 12px;
                padding: 20px;
                min-height: 140px;
            }

            #statItemIcon {
                font-size: 34px;
            }

            #statItemValue {
                color: #FFD700;
                font-size: 28px;
                font-weight: 300;
                letter-spacing: 1px;
            }

            #statItemLabel {
                color: #A0A0C0;
                font-size: 13px;
                letter-spacing: 1px;
                font-weight: 400;
            }

            QStatusBar {
                background-color: rgba(10, 15, 30, 0.95);
                color: #A0A0C0;
                font-size: 12px;
                letter-spacing: 0.5px;
                border-top: 1px solid rgba(255, 215, 0, 0.08);
            }
        )");
    }

    void addOutput(const QString &message, const QString &color = "#FFD700") {
        if (!output) return;
        output->append(QString("<span style='color: %1;'>%2</span>").arg(color, message));
        QTimer::singleShot(100, [this]() { if (output) output->moveCursor(QTextCursor::End); });
    }

    void clearInputs() {
        if (idInput) idInput->clear();
        if (nameInput) nameInput->clear();
        if (yearInput) yearInput->clear();
        if (dormCombo) dormCombo->setCurrentIndex(0);
        if (roomCombo) roomCombo->setCurrentIndex(0);
    }

    void onLogout() {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Logout",
                                                                  "Are you sure you want to logout?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            saveDataToUniversity();
            this->close();
            LoginDialog loginDialog;
            if (loginDialog.exec() == QDialog::Accepted) {
                ModernUniversityGUI *newWindow = new ModernUniversityGUI(loginDialog.getLoggedInUser());
                newWindow->show();
            }
        }
    }

    // ==================== SLOTS ====================

    void onRestaurantSelected(QListWidgetItem *item) {
        if (!item) return;
        QString text = item->text();
        QString name = text.split(" 🍽️ ").first();

        for (int i = 0; i < restaurantData.size(); i++) {
            if (restaurantData[i].name == name) {
                currentRestaurant = name;
                displayMeals(i);
                break;
            }
        }
    }

    void onAddStudent() {
        if (!idInput || !nameInput || !yearInput) return;

        bool ok;
        int id = idInput->text().toInt(&ok);
        if (!ok || id <= 0) {
            addOutput("❌ Invalid ID!", "#E74C3C");
            return;
        }

        QString nameStr = nameInput->text();
        if (nameStr.isEmpty()) {
            addOutput("❌ Invalid name!", "#E74C3C");
            return;
        }

        int year = yearInput->text().toInt(&ok);
        if (!ok || year <= 0 || year > 5) {
            addOutput("❌ Invalid year! (1-5)", "#E74C3C");
            return;
        }

        // Check both the real model AND the local cache for duplicates
        Student* existing = uni->search_Student(id);
        bool existsLocally = false;
        for (const StudentInfo &s : studentData) {
            if (s.id == id) { existsLocally = true; break; }
        }
        if (existing != nullptr || existsLocally) {
            addOutput("❌ Student ID already exists!", "#E74C3C");
            return;
        }

        // Persist in the real model
        uni->addStudent(id, nameStr.toStdString(), year);

        // Keep the local cache in sync - this is what the table is rebuilt from
        StudentInfo info;
        info.id = id;
        info.name = nameStr;
        info.year = year;
        info.dormitory = "—";
        info.room = "—";
        studentData.append(info);

        refreshStudentTable();
        addOutput(QString("✅ Student added: %1 (ID: %2)").arg(nameStr).arg(id));
        clearInputs();
        updateStatsPage();
        uni->saveAll();
    }

    void onRemoveStudent() {
        if (!idInput) return;

        bool ok;
        int id = idInput->text().toInt(&ok);
        if (!ok || id <= 0) {
            addOutput("❌ Please enter a valid student ID.", "#E74C3C");
            return;
        }

        int foundIndex = -1;
        for (int i = 0; i < studentData.size(); i++) {
            if (studentData[i].id == id) { foundIndex = i; break; }
        }

        if (foundIndex < 0) {
            addOutput(QString("❌ Student not found: %1").arg(id), "#E74C3C");
            return;
        }

        // Free up the room slot (if any) before removing
        const QString &dorm = studentData[foundIndex].dormitory;
        const QString &room = studentData[foundIndex].room;
        if (dorm != "—" && room != "—") {
            QString key = dorm + "|" + room;
            int newOcc = roomOccupancy.value(key, 0) - 1;
            roomOccupancy[key] = newOcc < 0 ? 0 : newOcc;
        }

        studentData.removeAt(foundIndex);
        uni->removeStudent(id); // best-effort sync with the real model

        refreshStudentTable();
        refreshRoomTable();
        refreshRoomComboForStudent();
        updateStatsPage();

        addOutput(QString("➖ Student removed: %1").arg(id));
        clearInputs();
        uni->saveAll();
    }

    // ------------------------------------------------------------------
    // THE FIX: previously this always called assignStudentToDormitory(),
    // which IGNORES whatever room you picked in roomCombo and instead lets
    // Dormitory::assignStudent() silently choose whichever room it finds
    // free first. Now, when a specific room is chosen, we call
    // University::assignStudentToRoom(id, dormName, roomNumber), which
    // assigns into that exact room. When "— None" is left selected, we
    // keep the old auto-pick-a-free-room behavior.
    // ------------------------------------------------------------------
    void onAssignStudent() {
        if (!idInput || !dormCombo) return;

        bool ok;
        int id = idInput->text().toInt(&ok);
        if (!ok || id <= 0) {
            addOutput("❌ Invalid ID!", "#E74C3C");
            return;
        }

        int dataIndex = -1;
        for (int i = 0; i < studentData.size(); i++) {
            if (studentData[i].id == id) { dataIndex = i; break; }
        }
        if (dataIndex < 0) {
            addOutput("❌ Student not found!", "#E74C3C");
            return;
        }

        QString dormStr = dormCombo->currentText();
        if (dormStr == "— None" || !dormitoryNames.contains(dormStr)) {
            addOutput("❌ Please select a valid dormitory.", "#E74C3C");
            return;
        }

        // currentData holds the real room number; the visible label also
        // shows occupancy text like "101 (1/2)", so we must not parse the text.
        QString roomStr = roomCombo ? roomCombo->currentData().toString() : QString();

        // If the user left "— None" selected, auto-pick the first room in
        // this dormitory that still has space, instead of calling the
        // room-blind assignStudentToDormitory(). Resolving a concrete room
        // number here, always, guarantees the table/occupancy reflect
        // exactly what the backend did.
        if (roomStr.isEmpty()) {
            for (const QString &candidateRoom : dormitoryData.value(dormStr)) {
                QString key = dormStr + "|" + candidateRoom;
                int cap = roomCapacities.value(key, 2);
                int occ = roomOccupancy.value(key, 0);
                if (occ < cap) {
                    roomStr = candidateRoom;
                    break;
                }
            }
            if (roomStr.isEmpty()) {
                addOutput("❌ No available room in that dormitory.", "#E74C3C");
                return;
            }
        }

        int roomNum = -1;
        {
            bool roomOk;
            roomNum = roomStr.toInt(&roomOk);
            if (!roomOk) {
                addOutput("❌ Invalid room number.", "#E74C3C");
                return;
            }

            QString key = dormStr + "|" + roomStr;
            int cap = roomCapacities.value(key, 2);
            int occ = roomOccupancy.value(key, 0);
            if (occ >= cap) {
                addOutput("❌ That room is already full!", "#E74C3C");
                return;
            }
        }

        // Free the student's previous room slot, if they had one
        QString prevDorm = studentData[dataIndex].dormitory;
        QString prevRoom = studentData[dataIndex].room;
        if (prevDorm != "—" && prevRoom != "—") {
            QString prevKey = prevDorm + "|" + prevRoom;
            int newOcc = roomOccupancy.value(prevKey, 0) - 1;
            roomOccupancy[prevKey] = newOcc < 0 ? 0 : newOcc;
        }

        // If the student currently has ANY assignment (here or elsewhere),
        // University::assignStudentToRoom / assignStudentToDormitory both
        // refuse to reassign — they only succeed for a student who is
        // currently unassigned anywhere. Detect that case up front so we
        // can give a clear message instead of the generic failure text.
        bool hadPreviousAssignment = (prevDorm != "—" && prevRoom != "—") ||
                                     (prevDorm != "—");

        bool success = uni->assignStudentToRoom(id, dormStr.toStdString(), roomNum);

        if (!success) {
            // Roll back the slot we just freed, since the assignment failed
            if (prevDorm != "—" && prevRoom != "—") {
                QString prevKey = prevDorm + "|" + prevRoom;
                roomOccupancy[prevKey] = roomOccupancy.value(prevKey, 0) + 1;
            }
            if (hadPreviousAssignment) {
                addOutput("❌ Assignment failed: this student is already assigned. Remove their current assignment first.", "#E74C3C");
            } else {
                addOutput("❌ Assignment failed. Room/Dormitory may be full or not found.", "#E74C3C");
            }
            return;
        }

        studentData[dataIndex].dormitory = dormStr;
        studentData[dataIndex].room = roomStr;

        QString key = dormStr + "|" + roomStr;
        roomOccupancy[key] = roomOccupancy.value(key, 0) + 1;

        refreshStudentTable();
        refreshRoomTable();
        refreshRoomComboForStudent();

        addOutput(QString("📌 Student %1 assigned to %2, Room %3").arg(id).arg(dormStr, roomStr));
        clearInputs();
        uni->saveAll();
    }

    void onClearAll() {
        clearInputs();
        addOutput("🗑️ Fields cleared", "#95A5A6");
    }

    void onAddDormitory() {
        if (!dormNameInput) return;

        QString name = dormNameInput->text().trimmed();
        if (name.isEmpty()) {
            addOutput("❌ Please enter a dormitory name.", "#E74C3C");
            return;
        }

        if (!createDormitoryInternal(name)) {
            addOutput("❌ Dormitory already exists!", "#E74C3C");
            return;
        }

        refreshDormitoryList();
        refreshDormCombo();
        refreshRoomDormCombo();
        updateDashboardStats();
        updateStatsPage();

        addOutput(QString("🏠 Dormitory added: %1").arg(name));
        dormNameInput->clear();
        uni->saveAll();
    }

    void onRemoveDormitory() {
        if (!dormList) return;

        int currentRow = dormList->currentRow();
        if (currentRow < 0 || currentRow >= dormitoryNames.size()) {
            addOutput("❌ Please select a dormitory.", "#E74C3C");
            return;
        }

        QString dormName = dormitoryNames[currentRow];

        if (uni->removeDormitory(dormName.toStdString())) {
            // Clean up every room that belonged to this dormitory
            for (const QString &room : dormitoryData.value(dormName)) {
                QString key = dormName + "|" + room;
                roomCapacities.remove(key);
                roomOccupancy.remove(key);
            }
            dormitoryNames.removeAt(currentRow);
            dormitoryData.remove(dormName);

            // Any student that was assigned here is now unassigned, instead
            // of silently pointing at a dormitory that no longer exists
            for (StudentInfo &s : studentData) {
                if (s.dormitory == dormName) {
                    s.dormitory = "—";
                    s.room = "—";
                }
            }

            refreshDormitoryList();
            refreshDormCombo();
            refreshRoomDormCombo();
            refreshStudentTable();
            refreshRoomComboForStudent();
            updateDashboardStats();
            updateStatsPage();

            addOutput(QString("➖ Dormitory removed: %1").arg(dormName));
            uni->saveAll();
        } else {
            addOutput("❌ Failed to remove dormitory.", "#E74C3C");
        }
    }

    void onAddRoom() {
        if (!roomDormCombo || !roomNumberInput) return;

        QString dormName = roomDormCombo->currentText();
        QString roomNumber = roomNumberInput->text().trimmed();

        if (dormName == "— None") {
            addOutput("❌ Please select a dormitory.", "#E74C3C");
            return;
        }

        if (roomNumber.isEmpty()) {
            addOutput("❌ Please enter a room number.", "#E74C3C");
            return;
        }

        bool numOk;
        roomNumber.toInt(&numOk);
        if (!numOk) {
            addOutput("❌ Room number must be numeric.", "#E74C3C");
            return;
        }

        int capacity = 2;
        if (roomCapacityInput) {
            bool ok;
            int parsed = roomCapacityInput->text().trimmed().toInt(&ok);
            if (ok && parsed > 0) capacity = parsed;
        }

        if (!addRoomInternal(dormName, roomNumber, capacity)) {
            addOutput("❌ Room already exists in this dormitory!", "#E74C3C");
            return;
        }

        refreshRoomTable();
        refreshDormitoryList();
        refreshRoomComboForStudent();
        updateDashboardStats();
        updateStatsPage();

        addOutput(QString("🚪 Room %1 added to %2 (capacity %3)").arg(roomNumber).arg(dormName).arg(capacity));
        roomNumberInput->clear();
        if (roomCapacityInput) roomCapacityInput->setText("2");
        uni->saveAll();
    }

    void onRemoveRoom() {
        if (!roomTable) return;

        int currentRow = roomTable->currentRow();
        if (currentRow < 0) {
            addOutput("❌ Please select a room.", "#E74C3C");
            return;
        }

        QString roomNumber = roomTable->item(currentRow, 0)->text();
        QString dormName = roomTable->item(currentRow, 1)->text();
        QString key = dormName + "|" + roomNumber;

        if (roomOccupancy.value(key, 0) > 0) {
            addOutput("❌ Cannot remove: this room still has students assigned to it.", "#E74C3C");
            return;
        }

        bool numOk;
        int roomNum = roomNumber.toInt(&numOk);
        if (numOk) {
            // Keep the real backend model in sync too, not just the local mirrors
            uni->removeRoomFromDormitory(dormName.toStdString(), roomNum);
        }

        if (dormitoryData.contains(dormName)) {
            dormitoryData[dormName].removeAll(roomNumber);
        }
        roomCapacities.remove(key);
        roomOccupancy.remove(key);

        refreshRoomTable();
        refreshDormitoryList();
        refreshRoomComboForStudent();
        updateDashboardStats();
        updateStatsPage();

        addOutput(QString("➖ Room %1 removed").arg(roomNumber));
        uni->saveAll();
    }

    void onAddRestaurant() {
        if (!restaurantNameInput || !restaurantCapacityInput) return;

        QString name = restaurantNameInput->text().trimmed();
        QString capacityStr = restaurantCapacityInput->text().trimmed();

        if (name.isEmpty() || capacityStr.isEmpty()) {
            addOutput("❌ Please enter all fields.", "#E74C3C");
            return;
        }

        bool ok;
        int capacity = capacityStr.toInt(&ok);
        if (!ok || capacity <= 0) {
            addOutput("❌ Please enter a valid capacity.", "#E74C3C");
            return;
        }

        // Check if exists
        for (const RestaurantInfo &rest : restaurantData) {
            if (rest.name == name) {
                addOutput("❌ Restaurant already exists!", "#E74C3C");
                return;
            }
        }

        RestaurantInfo newRest;
        newRest.name = name;
        newRest.capacity = capacity;
        restaurantData.append(newRest);

        refreshRestaurantList();
        updateDashboardStats();
        updateStatsPage();

        addOutput(QString("🍽️ Restaurant added: %1 (Capacity: %2)").arg(name).arg(capacity));
        restaurantNameInput->clear();
        restaurantCapacityInput->clear();
        uni->saveAll();
    }

    void onRemoveRestaurant() {
        if (!restaurantList) return;

        int currentRow = restaurantList->currentRow();
        if (currentRow < 0) {
            addOutput("❌ Please select a restaurant.", "#E74C3C");
            return;
        }

        QString itemText = restaurantList->currentItem()->text();
        QString name = itemText.split(" 🍽️ ").first();

        for (int i = 0; i < restaurantData.size(); i++) {
            if (restaurantData[i].name == name) {
                restaurantData.removeAt(i);
                break;
            }
        }

        refreshRestaurantList();
        updateDashboardStats();
        updateStatsPage();

        addOutput(QString("➖ Restaurant removed: %1").arg(name));
        uni->saveAll();
    }

    void onAddMeal() {
        if (!restaurantList || !mealTypeCombo || !mealItemInput) return;

        int currentRow = restaurantList->currentRow();
        if (currentRow < 0) {
            addOutput("❌ Please select a restaurant first.", "#E74C3C");
            return;
        }

        QString mealType = mealTypeCombo->currentText();
        QString mealItem = mealItemInput->text().trimmed();

        if (mealItem.isEmpty()) {
            addOutput("❌ Please enter a meal item.", "#E74C3C");
            return;
        }

        RestaurantInfo &rest = restaurantData[currentRow];
        if (mealType == "🌅 Breakfast") {
            rest.breakfast.append(mealItem);
        } else if (mealType == "☀️ Lunch") {
            rest.lunch.append(mealItem);
        } else if (mealType == "🌙 Dinner") {
            rest.dinner.append(mealItem);
        }

        displayMeals(currentRow);
        addOutput(QString("✅ Added '%1' to %2 (%3)").arg(mealItem).arg(rest.name).arg(mealType));
        mealItemInput->clear();
        uni->saveAll();
    }

    void onRemoveMeal() {
        if (!mealTable || !restaurantList) return;

        int currentRow = restaurantList->currentRow();
        if (currentRow < 0) {
            addOutput("❌ Please select a restaurant first.", "#E74C3C");
            return;
        }

        int mealRow = mealTable->currentRow();
        if (mealRow < 0) {
            addOutput("❌ Please select a meal to remove.", "#E74C3C");
            return;
        }

        QString mealType = mealTable->item(mealRow, 0)->text();
        QString mealItems = mealTable->item(mealRow, 1)->text();

        if (mealItems.isEmpty() || mealItems == " ") {
            addOutput("❌ No items to remove.", "#E74C3C");
            return;
        }

        QStringList items = mealItems.split(", ");
        if (items.isEmpty()) return;

        QString lastItem = items.last();
        items.removeLast();

        RestaurantInfo &rest = restaurantData[currentRow];
        if (mealType.contains("Breakfast")) {
            rest.breakfast.removeAll(lastItem);
        } else if (mealType.contains("Lunch")) {
            rest.lunch.removeAll(lastItem);
        } else if (mealType.contains("Dinner")) {
            rest.dinner.removeAll(lastItem);
        }

        displayMeals(currentRow);
        addOutput(QString("➖ Removed '%1' from %2").arg(lastItem).arg(mealType));
        uni->saveAll();
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");

    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        ModernUniversityGUI window(loginDialog.getLoggedInUser());
        window.show();
        return app.exec();
    }
    return 0;
}

#include "main.moc"