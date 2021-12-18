#include "widget.h"
#include "ui_widget.h"

//#define GAME_STOPED 0
//#define GAME_STARTED 1

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
     // Устанавливаем параметры окна приложения
    this->resize(600,640);          // Задаем размеры виджета, то есть окна
    this->setFixedSize(600,640);    // Фиксируем размеры виджета, чтобы окно нельзя было растянуть или уменьшить

    scene = new CustomScene();  //создаём сцену
    ui->graphicsView->setScene(scene);  //Устанавливаем сцену
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Устанавливаем сглаживание краёв
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали
    scene->setSceneRect(-250,-250,500,500);    // Устанавливаем размеры графической сцены

    timer = new QTimer();
    timerCreateApple = new QTimer();

    gameState = GAME_STOPED;
    //connect(count, &Widget::signalCheckGameOver, this, &Widget::slotGameOver);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotDeleteApple(QGraphicsItem *item)
{
    /* Получив сигнал от Мухи
     * Перебираем весь список яблок и удаляем найденное яблоко
     * */
    foreach (QGraphicsItem *apple, apples) {
        if(apple == item){
            scene->removeItem(apple);   // Удаляем со сцены
            apples.removeOne(item);     // Удаляем из списка
            delete apple;               // Вообще удаляем
            count++;

            ui->lcdNumber->display(count);  /* Увеличиваем счёт на единицу
                                              * и отображаем на дисплее
                                                 * */
            if(count > 10)
                slotWin();

            // Звук поедания яблока
            QMediaPlayer * m_player = new QMediaPlayer(this);   // Инициализируем плеер
            QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player); // Создаём плейлист
            m_player->setPlaylist(m_playlist);  // Устанавливаем плейлист в плеер
            m_playlist->addMedia(QUrl("qrc:/gamesound/hrum.wav")); // Добавляем аудио в плеер
            m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce); // Проигрываем один раз
            m_player->play();   // Запускаем плеер


        }
    }
}

void Widget::slotCreateApple()
{
    Apple *apple = new Apple(); // Создаём яблоко
    scene->addItem(apple);      // Помещаем его в сцену со случайной позицией
    apple->setPos((qrand() % (251)) * ((qrand()%2 == 1)?1:-1),
                  (qrand() % (251)) * ((qrand()%2 == 1)?1:-1));
    apple->setZValue(-1);       /* Помещаем яблоко ниже Мухи, то есть Муха
                                 * на сцене будет выше яблок
                                 * */
    apples.append(apple);       // Добавляем Яблоко в Список
}

void Widget::on_pushButton_clicked()
{
    count = 0;
    ui->lcdNumber->display(count);
    triangle = new Triangle();
    scene->addItem(triangle);
    triangle->setPos(0,0);

    spider = new Spider(triangle);
    scene->addItem(spider);
    spider->setPos(280,280);

    connect(spider, &Spider::signalCheckGameOver, this, &Widget::slotGameOver);

    connect(timer, &QTimer::timeout, triangle, &Triangle::slotGameTimer);
    timer->start(1000 / 100);
    // Соединяем сигнал о положении курсора со слотом для передвижения героя
    connect(scene, &CustomScene::signalTargetCoordinate, triangle, &Triangle::slotTarget);

    connect(timerCreateApple, &QTimer::timeout, this, &Widget::slotCreateApple);
    timerCreateApple->start(1000);

    connect(triangle, &Triangle::signalCheckItem, this, &Widget::slotDeleteApple);

    ui->pushButton->setEnabled(false);    

    gameState = GAME_STARTED;
}

void Widget::slotGameOver()
{
    timer->stop();
    timerCreateApple->stop();

    QMediaPlayer * m_player = new QMediaPlayer(this);       // Создаём плеер
    QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player); // Создаём плейлист
    m_player->setPlaylist(m_playlist);      // Устанавливаем плейлист в плеер
    m_playlist->addMedia(QUrl("qrc:/gamesound/scream.wav")); // Добавляем аудио в плейлист
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);   // Проигрываем трек один раз
    m_player->play();   // Запускаем трек

    QMessageBox::warning(this, "Game Over", "Очень жаль, но вас съели!");

    disconnect(timerCreateApple, &QTimer::timeout, this, &Widget::slotCreateApple);
    disconnect(triangle, &Triangle::signalCheckItem, this, &Widget::slotDeleteApple);
    disconnect(spider, &Spider::signalCheckGameOver, this, &Widget::slotGameOver);

    spider->deleteLater();
    triangle->deleteLater();

    foreach (QGraphicsItem *apple, apples) {
        scene->removeItem(apple);
        apples.removeOne(apple);
        delete apple;
    }

    ui->pushButton->setEnabled(true);

    gameState = GAME_STOPED;
}


void Widget::slotWin()
{
    spider->SPtimer->stop();
    timer->stop();
    timerCreateApple->stop();
    disconnect(spider, &Spider::signalCheckGameOver, this, &Widget::slotGameOver);
    spider->deleteLater();
    disconnect(timerCreateApple, &QTimer::timeout, this, &Widget::slotCreateApple);
    disconnect(triangle, &Triangle::signalCheckItem, this, &Widget::slotDeleteApple);
    triangle->deleteLater();

    foreach (QGraphicsItem *apple, apples) {
        scene->removeItem(apple);
        apples.removeOne(apple);
        delete apple;
    }
    gameState = GAME_STOPED;

    QMediaPlayer * m_player = new QMediaPlayer(this);       // Создаём плеер
    QMediaPlaylist * m_playlist = new QMediaPlaylist(m_player); // Создаём плейлист
    m_player->setPlaylist(m_playlist);      // Устанавливаем плейлист в плеер
    m_playlist->addMedia(QUrl("qrc:/gamesound/win.wav")); // Добавляем аудио в плейлист
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);   // Проигрываем трек один раз
    m_player->play();   // Запускаем трек

    QMessageBox::warning(this, "Win", "Вы выиграли!");

    ui->pushButton->setEnabled(true);

}

