#include "DOS.h"
#include "ui_DOS.h"

DOS::DOS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DOS)
{
    m_init = 0;
    ui->setupUi(this);
    this->Init();
    if(parent != 0)
    {
        m_parent = 1;
    }
    //-------------------Set Template-----------------------------------------------------------------------//
    tp = new DOS_Template();
    tp->setGeometry(this->geometry());
    tp->move(this->geometry().x()+20,this->geometry().y()+20);
    tp->show();
    if(qApp->screens().count() > 1)
    {
        tp->setGeometry(qApp->screens()[1]->geometry());
        tp->setGeometry(tp->x()+50,tp->y()+70,tp->width()-100,tp->height()-100);
        tp->windowHandle()->setScreen(qApp->screens()[1]);
    }
    if(this->isFullScreen())
    {
        tp->showFullScreen();
    }
    this->activateWindow();
    connect(tp,SIGNAL(on_Exit()),this,SLOT(on_ExitBtn_clicked()));
    connect(tp,SIGNAL(on_FullscreenBtn()),this,SLOT(on_FullscreenBtn_clicked()));
    connect(tp,SIGNAL(on_MinimizeBtn()),this,SLOT(on_MinimizeBtn_clicked()));
    connect(this,SIGNAL(update_Template(GFuncShare::DOS_DataTemplate)),tp,SLOT(Update_template(GFuncShare::DOS_DataTemplate)));

    //-------------------Set Time---------------------------------------------------------------------------//
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(Update_CurrentTime()));
    ui->st_TimeDisplay_Lb->setText(QDateTime::currentDateTimeUtc().toString("hh:mm"));
    ui->m_TimeDisplay_Lb->setText(QDateTime::currentDateTimeUtc().toString("hh:mm"));
    timer->start(1000);
}
//----------------------------------------------------------------------------------------------------------//
DOS::~DOS()
{
    delete ui;
    delete tp;
}
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
//-------------------------------------> Event Function <---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
void DOS::resizeEvent(QResizeEvent *rs)
{
    sx = double(rs->size().width())/1920.0;
    sy = double(rs->size().height())/1200.0;

    //---------------------Main Page------------------------------------------------------------------------//
    ui->ExitBtn->setGeometry(1870*sx,20*sy,31*sx,31*sy);
    ui->FullscreenBtn->setGeometry(1835*sx,20*sy,31*sx,31*sy);
    ui->MinimizeBtn->setGeometry(1800*sx,20*sy,31*sx,31*sy);

    //---------------------Menu Widget----------------------------------------------------------------------//
    if(m_menu)ui->Menu->setGeometry(405*sx,0,183*sx,1142*sy);
    else ui->Menu->setGeometry(405*sx,-1080*sy,183*sx,1142*sy);
    ui->me_bg->setGeometry(0,0,ui->Menu->width(),ui->Menu->height());

    ui->me_HomeBtn->setGeometry(49*sx,88*sy,62*sx,82*sy);
    ui->me_SettingBtn->setGeometry(45*sx,219*sy,62*sx,83*sy);
    ui->me_PlotBtn->setGeometry(49*sx,352*sy,69*sx,86*sy);
    ui->me_SaveBtn->setGeometry(62*sx,722*sy,34*sx,60*sy);
    ui->me_SentBtn->setGeometry(55*sx,821*sy,49*sx,53*sy);
    ui->me_ArchiveBtn->setGeometry(55*sx,911*sy,51*sx,67*sy);
    ui->me_PrintBtn->setGeometry(57*sx,1013*sy,45*sx,70*sy);
    ui->me_UDBtn->setGeometry(66*sx,1096*sy,27*sx,16*sy);


    QFont ff0 = ui->st_TimeDisplay_Lb->font();
    QFont ff1 = ui->st_H1_Lb->font();
    QFont ff2 = ui->st_H2_Lb->font();
    QFont ff3 = ui->setOKBtn->font();
    QFont ff4 = ui->m_H1_Lb->font();
    QFont ff5 = ui->m_in_Lb1->font();
    QFont ff6 = ui->m_Lb1->font();
    QFont ff7 = ui->m_outT_SpoolPte->font();
    QFont ff8 = ui->Epoch_1->font();

    if(sx < sy)
    {
        ff0.setPointSize(34*sx);
        ff1.setPointSize(28*sx);
        ff2.setPointSize(20*sx);
        ff3.setPointSize(22*sx);
        ff4.setPointSize(24*sx);
        ff5.setPointSize(18*sx);
        ff6.setPointSize(12*sx);
        ff7.setPointSize(14*sx);
        ff8.setPointSize(16*sx);
    }
    else
    {
        ff0.setPointSize(34*sy);
        ff1.setPointSize(28*sy);
        ff2.setPointSize(20*sy);
        ff3.setPointSize(22*sy);
        ff4.setPointSize(24*sy);
        ff5.setPointSize(18*sy);
        ff6.setPointSize(12*sy);
        ff7.setPointSize(14*sy);
        ff8.setPointSize(16*sy);
    }

    ui->st_TimeDisplay_Lb->setGeometry(1710*sx,90*sy,130*sx,50*sy);
    ui->st_TimeDisplay_Lb->setFont(ff0);

        //-----------------Sup page-----------------------------------------------------------------------//
        ui->SW->setGeometry(0,0,rs->size().width(),rs->size().height());
        ui->page_Main->setGeometry(0,0,ui->SW->width(),ui->SW->height());
        ui->page_setting->setGeometry(0,0,ui->SW->width(),ui->SW->height());
        ui->st_bg->setGeometry(0,0,ui->SW->width(),ui->SW->height());
        ui->m_bg->setGeometry(0,0,ui->SW->width(),ui->SW->height());

            //-------------Setting page-------------------------------------------------------------------//
            ui->st_bg_sub->setGeometry(60*sx,310*sy,1798*sx,799*sy);
            ui->st_H1_Lb->setGeometry(1489*sx,160*sy,350*sx,40*sy);
            ui->st_H1_Lb->setFont(ff1);
            ui->st_H2_Lb->setGeometry(1490*sx,200*sy,350*sx,30*sy);
            ui->st_H2_Lb->setFont(ff2);
            ui->st_BackBtn->setGeometry(1340*sx,210*sy,45*sx,41*sy);
            ui->st_BackBtn->setIconSize(QSize(43*sx,39*sy));

            ui->sup_setting->setGeometry(490*sx,330*sy,1340*sx,715*sy);
            ui->sup_setting_1->setGeometry(0,0,ui->sup_setting->width(),ui->sup_setting->height());
            ui->sup_setting_2->setGeometry(0,0,ui->sup_setting->width(),ui->sup_setting->height());
            ui->sup_setting_3->setGeometry(0,0,ui->sup_setting->width(),ui->sup_setting->height());
            ui->sup_setting_4->setGeometry(0,0,ui->sup_setting->width(),ui->sup_setting->height());
            ui->sup_setting_5->setGeometry(0,0,ui->sup_setting->width(),ui->sup_setting->height());
            ui->sup_setting_6->setGeometry(0,0,ui->sup_setting->width(),ui->sup_setting->height());
            ui->sup_setting_7->setGeometry(0,0,ui->sup_setting->width(),ui->sup_setting->height());

            ui->setPgBtn_1->setGeometry(60*sx,338*sy,407*sx,176*sy);
            ui->setPgBtn_1->setFont(ff2);
            ui->setPgBtn_2->setGeometry(ui->setPgBtn_1->x(),513*sy,ui->setPgBtn_1->width(),ui->setPgBtn_1->height());
            ui->setPgBtn_2->setFont(ff2);
            ui->setPgBtn_3->setGeometry(ui->setPgBtn_1->x(),689*sy,ui->setPgBtn_1->width(),ui->setPgBtn_1->height());
            ui->setPgBtn_3->setFont(ff2);
            ui->setPgBtn_4->setGeometry(ui->setPgBtn_1->x(),864*sy,ui->setPgBtn_1->width(),ui->setPgBtn_1->height());
            ui->setPgBtn_4->setFont(ff2);

            ui->setBackBtn->setGeometry(539*sx,1059*sy,16*sx,29*sy);
            ui->setBackBtn->setIconSize(QSize(14*sx,27*sy));
            ui->setNextBtn->setGeometry(591*sx,ui->setBackBtn->y(),ui->setBackBtn->width(),ui->setBackBtn->height());
            ui->setNextBtn->setIconSize(ui->setBackBtn->iconSize());
            ui->setOKBtn->setGeometry(1702*sx,1050*sy,87*sx,47*sy);
            ui->setOKBtn->setFont(ff3);

                //------------sup setting page 1--------------------------------------------------------------//
                ui->SLPN_1->setGeometry(20*sx,10*sy,750*sx,68*sy);
                ui->SLPN_1->setFont(ff2);
                ui->SLPN_2->setGeometry(ui->SLPN_1->x(),80*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_2->setFont(ff2);
                ui->SLPN_3->setGeometry(ui->SLPN_1->x(),150*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_3->setFont(ff2);
                ui->SLPN_4->setGeometry(ui->SLPN_1->x(),220*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_4->setFont(ff2);
                ui->SLPN_5->setGeometry(ui->SLPN_1->x(),290*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_5->setFont(ff2);
                ui->SLPN_6->setGeometry(ui->SLPN_1->x(),360*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_6->setFont(ff2);
                ui->SLPN_7->setGeometry(ui->SLPN_1->x(),430*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_7->setFont(ff2);
                ui->SLPN_8->setGeometry(ui->SLPN_1->x(),500*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_8->setFont(ff2);
                ui->SLPN_9->setGeometry(ui->SLPN_1->x(),570*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_9->setFont(ff2);
                ui->SLPN_10->setGeometry(ui->SLPN_1->x(),640*sy,ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_10->setFont(ff2);

                ui->SV_QDS_1->setGeometry(827*sx,23*sy,311*sx,42*sy);
                ui->SV_QDS_1->setFont(ff2);
                ui->SV_QDS_2->setGeometry(ui->SV_QDS_1->x(),93*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_2->setFont(ff2);
                ui->SV_QDS_3->setGeometry(ui->SV_QDS_1->x(),163*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_3->setFont(ff2);
                ui->SV_QDS_4->setGeometry(ui->SV_QDS_1->x(),233*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_4->setFont(ff2);
                ui->SV_QDS_5->setGeometry(ui->SV_QDS_1->x(),303*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_5->setFont(ff2);
                ui->SV_QDS_6->setGeometry(ui->SV_QDS_1->x(),373*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_6->setFont(ff2);
                ui->SV_QDS_7->setGeometry(ui->SV_QDS_1->x(),443*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_7->setFont(ff2);
                ui->SV_QDS_8->setGeometry(ui->SV_QDS_1->x(),513*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_8->setFont(ff2);
                ui->SV_QDS_9->setGeometry(ui->SV_QDS_1->x(),583*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_9->setFont(ff2);
                ui->SV_QDS_10->setGeometry(ui->SV_QDS_1->x(),653*sy,ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_10->setFont(ff2);

                ui->SLPU_1->setGeometry(1210*sx,ui->SLPN_1->y(),120*sx,ui->SLPN_1->height());
                ui->SLPU_1->setFont(ff2);
                ui->SLPU_2->setGeometry(ui->SLPU_1->x(),ui->SLPN_2->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_2->setFont(ff2);
                ui->SLPU_3->setGeometry(ui->SLPU_1->x(),ui->SLPN_3->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_3->setFont(ff2);
                ui->SLPU_4->setGeometry(ui->SLPU_1->x(),ui->SLPN_4->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_4->setFont(ff2);
                ui->SLPU_5->setGeometry(ui->SLPU_1->x(),ui->SLPN_5->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_5->setFont(ff2);
                ui->SLPU_6->setGeometry(ui->SLPU_1->x(),ui->SLPN_6->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_6->setFont(ff2);
                ui->SLPU_7->setGeometry(ui->SLPU_1->x(),ui->SLPN_7->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_7->setFont(ff2);
                ui->SLPU_8->setGeometry(ui->SLPU_1->x(),ui->SLPN_8->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_8->setFont(ff2);
                ui->SLPU_9->setGeometry(ui->SLPU_1->x(),ui->SLPN_9->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_9->setFont(ff2);
                ui->SLPU_10->setGeometry(ui->SLPU_1->x(),ui->SLPN_10->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_10->setFont(ff2);

                //------------sup setting page 2--------------------------------------------------------------//
                ui->SLPN_11->setGeometry(ui->SLPN_1->x(),ui->SLPN_1->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_11->setFont(ff2);
                ui->SLPN_12->setGeometry(ui->SLPN_1->x(),ui->SLPN_2->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_12->setFont(ff2);
                ui->SLPN_13->setGeometry(ui->SLPN_1->x(),ui->SLPN_3->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_13->setFont(ff2);
                ui->SLPN_14->setGeometry(ui->SLPN_1->x(),ui->SLPN_4->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_14->setFont(ff2);
                ui->SLPN_15->setGeometry(ui->SLPN_1->x(),ui->SLPN_5->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_15->setFont(ff2);
                ui->SLPN_16->setGeometry(ui->SLPN_1->x(),ui->SLPN_6->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_16->setFont(ff2);
                ui->SLPN_17->setGeometry(ui->SLPN_1->x(),ui->SLPN_7->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_17->setFont(ff2);
                ui->SLPN_18->setGeometry(ui->SLPN_1->x(),ui->SLPN_8->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_18->setFont(ff2);
                ui->SLPN_19->setGeometry(ui->SLPN_1->x(),ui->SLPN_9->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_19->setFont(ff2);
                ui->SLPN_20->setGeometry(ui->SLPN_1->x(),ui->SLPN_10->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_20->setFont(ff2);

                ui->SV_QDS_11->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_1->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_11->setFont(ff2);
                ui->SV_QDS_12->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_2->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_12->setFont(ff2);
                ui->SV_QDS_13->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_3->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_13->setFont(ff2);
                ui->SV_QDS_14->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_4->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_14->setFont(ff2);
                ui->SV_QDS_15->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_5->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_15->setFont(ff2);
                ui->SV_QDS_16->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_6->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_16->setFont(ff2);
                ui->SV_QDS_17->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_7->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_17->setFont(ff2);
                ui->SV_QDS_18->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_8->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_18->setFont(ff2);
                ui->SV_QDS_19->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_9->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_19->setFont(ff2);
                ui->SV_QDS_20->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_10->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_20->setFont(ff2);

                ui->SLPU_12->setGeometry(ui->SLPU_1->x(),ui->SLPN_2->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_12->setFont(ff2);

                //------------sup setting page 3--------------------------------------------------------------//
                ui->SLPN_21->setGeometry(ui->SLPN_1->x(),ui->SLPN_1->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_21->setFont(ff2);
                ui->SLPN_22->setGeometry(ui->SLPN_1->x(),ui->SLPN_2->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_22->setFont(ff2);
                ui->SLPN_23->setGeometry(ui->SLPN_1->x(),ui->SLPN_3->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_23->setFont(ff2);
                ui->SLPN_24->setGeometry(ui->SLPN_1->x(),ui->SLPN_4->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_24->setFont(ff2);
                ui->SLPN_25->setGeometry(ui->SLPN_1->x(),ui->SLPN_5->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_25->setFont(ff2);
                ui->SLPN_26->setGeometry(ui->SLPN_1->x(),ui->SLPN_6->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_26->setFont(ff2);
                ui->SLPN_27->setGeometry(ui->SLPN_1->x(),ui->SLPN_7->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_27->setFont(ff2);
                ui->SLPN_28->setGeometry(ui->SLPN_1->x(),ui->SLPN_8->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_28->setFont(ff2);
                ui->SLPN_29->setGeometry(ui->SLPN_1->x(),ui->SLPN_9->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_29->setFont(ff2);
                ui->SLPN_30->setGeometry(ui->SLPN_1->x(),ui->SLPN_10->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_30->setFont(ff2);

                ui->SV_QDS_21->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_1->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_21->setFont(ff2);
                ui->SV_QDS_22->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_2->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_22->setFont(ff2);
                ui->SV_QDS_23->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_3->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_23->setFont(ff2);
                ui->SV_QDS_24->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_4->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_24->setFont(ff2);
                ui->SV_QDS_25->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_5->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_25->setFont(ff2);
                ui->SV_QDS_26->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_6->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_26->setFont(ff2);
                ui->SV_QDS_27->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_7->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_27->setFont(ff2);
                ui->SV_QDS_28->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_8->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_28->setFont(ff2);
                ui->SV_QDS_29->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_9->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_29->setFont(ff2);
                ui->SV_QDS_30->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_10->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_30->setFont(ff2);

                ui->SLPU_25->setGeometry(ui->SLPU_1->x(),ui->SLPN_5->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_25->setFont(ff2);

                //------------sup setting page 4--------------------------------------------------------------//
                ui->SLPN_31->setGeometry(ui->SLPN_1->x(),ui->SLPN_1->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_31->setFont(ff2);
                ui->SLPN_32->setGeometry(ui->SLPN_1->x(),ui->SLPN_2->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_32->setFont(ff2);
                ui->SLPN_33->setGeometry(ui->SLPN_1->x(),ui->SLPN_3->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_33->setFont(ff2);
                ui->SLPN_34->setGeometry(ui->SLPN_1->x(),ui->SLPN_4->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_34->setFont(ff2);
                ui->SLPN_35->setGeometry(ui->SLPN_1->x(),ui->SLPN_5->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_35->setFont(ff2);
                ui->SLPN_36->setGeometry(ui->SLPN_1->x(),ui->SLPN_6->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_36->setFont(ff2);
                ui->SLPN_37->setGeometry(ui->SLPN_1->x(),ui->SLPN_7->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_37->setFont(ff2);
                ui->SLPN_38->setGeometry(ui->SLPN_1->x(),ui->SLPN_8->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_38->setFont(ff2);
                ui->SLPN_39->setGeometry(ui->SLPN_1->x(),ui->SLPN_9->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_39->setFont(ff2);

                ui->SV_QDS_31->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_1->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_31->setFont(ff2);
                ui->SV_QDS_32->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_2->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_32->setFont(ff2);
                ui->SV_QDS_33->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_3->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_33->setFont(ff2);
                ui->SV_QDS_34->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_4->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_34->setFont(ff2);
                ui->SV_QDS_35->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_5->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_35->setFont(ff2);
                ui->SV_QDS_36->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_6->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_36->setFont(ff2);
                ui->SV_QDS_37->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_7->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_37->setFont(ff2);
                ui->SV_QDS_38->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_8->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_38->setFont(ff2);
                ui->SV_QDS_39->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_9->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_39->setFont(ff2);

                ui->SLPU_38->setGeometry(ui->SLPU_1->x(),ui->SLPN_8->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_38->setFont(ff2);
                ui->SLPU_39->setGeometry(ui->SLPU_1->x(),ui->SLPN_9->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_39->setFont(ff2);

                //------------sup setting page 5--------------------------------------------------------------//
                ui->SLPN_41->setGeometry(ui->SLPN_1->x(),ui->SLPN_1->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_41->setFont(ff2);
                ui->SLPN_42->setGeometry(ui->SLPN_1->x(),ui->SLPN_2->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_42->setFont(ff2);
                ui->SLPN_43->setGeometry(ui->SLPN_1->x(),ui->SLPN_3->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_43->setFont(ff2);
                ui->SLPN_44->setGeometry(ui->SLPN_1->x(),ui->SLPN_4->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_44->setFont(ff2);
                ui->SLPN_45->setGeometry(ui->SLPN_1->x(),ui->SLPN_5->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_45->setFont(ff2);
                ui->SLPN_46->setGeometry(ui->SLPN_1->x(),ui->SLPN_6->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_46->setFont(ff2);
                ui->SLPN_47->setGeometry(ui->SLPN_1->x(),ui->SLPN_7->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_47->setFont(ff2);
                ui->SLPN_48->setGeometry(ui->SLPN_1->x(),ui->SLPN_8->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_48->setFont(ff2);
                ui->SLPN_49->setGeometry(ui->SLPN_1->x(),ui->SLPN_9->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_49->setFont(ff2);
                ui->SLPN_50->setGeometry(ui->SLPN_1->x(),ui->SLPN_10->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_50->setFont(ff2);

                ui->SV_QDS_41->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_1->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_41->setFont(ff2);
                ui->SV_QDS_42->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_2->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_42->setFont(ff2);
                ui->SV_QDS_43->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_3->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_43->setFont(ff2);
                ui->SV_QDS_44->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_4->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_44->setFont(ff2);
                ui->SV_QDS_45->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_5->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_45->setFont(ff2);
                ui->SV_QDS_46->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_6->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_46->setFont(ff2);
                ui->SV_QDS_47->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_7->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_47->setFont(ff2);
                ui->SV_QDS_48->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_8->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_48->setFont(ff2);
                ui->SV_QDS_49->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_9->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_49->setFont(ff2);
                ui->SV_QDS_50->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_10->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_50->setFont(ff2);

                ui->SLPU_41->setGeometry(ui->SLPU_1->x(),ui->SLPN_1->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_41->setFont(ff2);
                ui->SLPU_42->setGeometry(ui->SLPU_1->x(),ui->SLPN_2->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_42->setFont(ff2);
                ui->SLPU_43->setGeometry(ui->SLPU_1->x(),ui->SLPN_3->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_43->setFont(ff2);
                ui->SLPU_44->setGeometry(ui->SLPU_1->x(),ui->SLPN_4->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_44->setFont(ff2);
                ui->SLPU_45->setGeometry(ui->SLPU_1->x(),ui->SLPN_5->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_45->setFont(ff2);
                ui->SLPU_46->setGeometry(ui->SLPU_1->x(),ui->SLPN_6->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_46->setFont(ff2);
                ui->SLPU_47->setGeometry(ui->SLPU_1->x(),ui->SLPN_7->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_47->setFont(ff2);
                ui->SLPU_48->setGeometry(ui->SLPU_1->x(),ui->SLPN_8->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_48->setFont(ff2);
                ui->SLPU_49->setGeometry(ui->SLPU_1->x(),ui->SLPN_9->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_49->setFont(ff2);
                ui->SLPU_50->setGeometry(ui->SLPU_1->x(),ui->SLPN_10->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_50->setFont(ff2);

                //------------sup setting page 6--------------------------------------------------------------//
                ui->SLPN_51->setGeometry(ui->SLPN_1->x(),ui->SLPN_1->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_51->setFont(ff2);
                ui->SLPN_52->setGeometry(ui->SLPN_1->x(),ui->SLPN_2->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_52->setFont(ff2);
                ui->SLPN_53->setGeometry(ui->SLPN_1->x(),ui->SLPN_3->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_53->setFont(ff2);
                ui->SLPN_54->setGeometry(ui->SLPN_1->x(),ui->SLPN_4->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_54->setFont(ff2);
                ui->SLPN_55->setGeometry(ui->SLPN_1->x(),ui->SLPN_5->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_55->setFont(ff2);
                ui->SLPN_56->setGeometry(ui->SLPN_1->x(),ui->SLPN_6->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_56->setFont(ff2);
                ui->SLPN_57->setGeometry(ui->SLPN_1->x(),ui->SLPN_7->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_57->setFont(ff2);
                ui->SLPN_58->setGeometry(ui->SLPN_1->x(),ui->SLPN_8->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_58->setFont(ff2);

                ui->SV_QDS_51->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_1->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_51->setFont(ff2);
                ui->SV_QDS_52->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_2->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_52->setFont(ff2);
                ui->SV_QDS_53->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_3->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_53->setFont(ff2);
                ui->SV_QDS_54->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_4->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_54->setFont(ff2);
                ui->SV_QDS_55->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_5->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_55->setFont(ff2);
                ui->SV_QDS_56->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_6->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_56->setFont(ff2);
                ui->SV_QDS_57->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_7->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_57->setFont(ff2);
                ui->SV_QDS_58->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_8->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_58->setFont(ff2);

                ui->SLPU_51->setGeometry(ui->SLPU_1->x(),ui->SLPN_1->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_51->setFont(ff2);
                ui->SLPU_52->setGeometry(ui->SLPU_1->x(),ui->SLPN_2->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_52->setFont(ff2);
                ui->SLPU_53->setGeometry(ui->SLPU_1->x(),ui->SLPN_3->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_53->setFont(ff2);
                ui->SLPU_54->setGeometry(ui->SLPU_1->x(),ui->SLPN_4->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_54->setFont(ff2);
                ui->SLPU_56->setGeometry(ui->SLPU_1->x(),ui->SLPN_6->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_56->setFont(ff2);
                ui->SLPU_57->setGeometry(ui->SLPU_1->x(),ui->SLPN_7->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_57->setFont(ff2);

                //------------sup setting page 7--------------------------------------------------------------//
                ui->SLPN_61->setGeometry(ui->SLPN_1->x(),ui->SLPN_1->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_61->setFont(ff2);
                ui->SLPN_62->setGeometry(ui->SLPN_1->x(),ui->SLPN_2->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_62->setFont(ff2);
                ui->SLPN_63->setGeometry(ui->SLPN_1->x(),ui->SLPN_3->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_63->setFont(ff2);
                ui->SLPN_64->setGeometry(ui->SLPN_1->x(),ui->SLPN_4->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_64->setFont(ff2);
                ui->SLPN_65->setGeometry(ui->SLPN_1->x(),ui->SLPN_5->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_65->setFont(ff2);
                ui->SLPN_66->setGeometry(ui->SLPN_1->x(),ui->SLPN_6->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_66->setFont(ff2);

                ui->SLPN_68->setGeometry(ui->SLPN_1->x(),ui->SLPN_8->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_68->setFont(ff2);
                ui->SLPN_69->setGeometry(ui->SLPN_1->x(),ui->SLPN_9->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_69->setFont(ff2);
                ui->SLPN_70->setGeometry(ui->SLPN_1->x(),ui->SLPN_10->y(),ui->SLPN_1->width(),ui->SLPN_1->height());
                ui->SLPN_70->setFont(ff2);

                ui->SV_QDS_61->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_1->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_61->setFont(ff2);
                ui->SV_QDS_62->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_2->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_62->setFont(ff2);
                ui->SV_QDS_63->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_3->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_63->setFont(ff2);
                ui->SV_QDS_64->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_4->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_64->setFont(ff2);
                ui->SV_QDS_65->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_5->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_65->setFont(ff2);
                ui->SV_QDS_66->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_6->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_66->setFont(ff2);

                ui->SV_QDS_68->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_8->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_68->setFont(ff2);
                ui->SV_QDS_69->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_9->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_69->setFont(ff2);
                ui->SV_QDS_70->setGeometry(ui->SV_QDS_1->x(),ui->SV_QDS_10->y(),ui->SV_QDS_1->width(),ui->SV_QDS_1->height());
                ui->SV_QDS_70->setFont(ff2);

                ui->SLPU_61->setGeometry(ui->SLPU_1->x(),ui->SLPN_1->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_61->setFont(ff2);
                ui->SLPU_62->setGeometry(ui->SLPU_1->x(),ui->SLPN_2->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_62->setFont(ff2);
                ui->SLPU_63->setGeometry(ui->SLPU_1->x(),ui->SLPN_3->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_63->setFont(ff2);
                ui->SLPU_64->setGeometry(ui->SLPU_1->x(),ui->SLPN_4->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_64->setFont(ff2);
                ui->SLPU_65->setGeometry(ui->SLPU_1->x(),ui->SLPN_5->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_65->setFont(ff2);
                ui->SLPU_66->setGeometry(ui->SLPU_1->x(),ui->SLPN_6->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_66->setFont(ff2);

                ui->SLPU_68->setGeometry(ui->SLPU_1->x(),ui->SLPN_8->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_68->setFont(ff2);
                ui->SLPU_69->setGeometry(ui->SLPU_1->x(),ui->SLPN_9->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_69->setFont(ff2);
                ui->SLPU_70->setGeometry(ui->SLPU_1->x(),ui->SLPN_10->y(),ui->SLPU_1->width(),ui->SLPN_1->height());
                ui->SLPU_70->setFont(ff2);

            //-------------Main page---------------------------------------------------------------------//
            ui->sub_Main->setGeometry(563*sx,92*sy,1357*sx,953*sy);
            ui->sub_Main2->setGeometry(0*sx,450*sy,400*sx,590*sy);
            ui->m_H1_Lb->setGeometry(1590*sx,1100*sy,300*sx,30*sy);
            ui->m_H1_Lb->setFont(ff4);
            ui->m_TimeDisplay_Lb->setGeometry(1790*sx,1140*sy,100*sx,ui->m_H1_Lb->height());
            ui->m_TimeDisplay_Lb->setFont(ff3);

            ui->m_PicUser_lb->setGeometry(131*sx,210*sy,140*sx,140*sy);
            ui->m_Lb1->setGeometry(10*sx,350*sy,380*sx,40*sy);
            ui->m_Lb1->setFont(ff6);

            ui->m_point1->setGeometry(1640*sx,65*sy,16*sx,17*sy);
            ui->m_point2->setGeometry(1670*sx,ui->m_point1->y(),ui->m_point1->width(),ui->m_point1->height());
            ui->m_point3->setGeometry(1700*sx,ui->m_point1->y(),ui->m_point1->width(),ui->m_point1->height());
            ui->m_point4->setGeometry(1730*sx,ui->m_point1->y(),ui->m_point1->width(),ui->m_point1->height());
            ui->m_next->setGeometry(1760*sx,67*sy,16*sx,13*sy);
            ui->m_back->setGeometry(1610*sx,ui->m_next->y(),ui->m_next->width(),ui->m_next->height());

                //-------------Input page MAN--------------------------------------------------------------------//
                ui->page_InputMAN->setGeometry(0,0,ui->sub_Main->width(),ui->sub_Main->height());
                ui->m_in_bg->setGeometry(0,0,ui->sub_Main->width(),ui->sub_Main->height());
                ui->m_in_StartBtn->setGeometry(1088*sx,890*sy,121*sx,44*sy);

                    //-------------Sub Input page------------------------------------------------------------//
                    ui->page_InputMAN_sub->setGeometry(0,0,ui->sub_Main2->width(),ui->sub_Main2->height());
                    ui->m_ins_Lb1->setGeometry(50*sx,50*sy,300*sx,40*sy);
                    ui->m_ins_Lb1->setFont(ff5);
                    ui->m_ins_Lb2->setGeometry(ui->m_ins_Lb1->x(),170*sy,ui->m_ins_Lb1->width(),ui->m_ins_Lb1->height());
                    ui->m_ins_Lb2->setFont(ff5);
                    ui->m_ins_Lb3->setGeometry(ui->m_ins_Lb1->x(),290*sy,ui->m_ins_Lb1->width(),ui->m_ins_Lb1->height());
                    ui->m_ins_Lb3->setFont(ff5);
                    ui->m_ins_Lb4->setGeometry(ui->m_ins_Lb1->x(),410*sy,ui->m_ins_Lb1->width(),ui->m_ins_Lb1->height());
                    ui->m_ins_Lb4->setFont(ff5);

                    ui->m_ins_HP_Dsb->setGeometry(ui->m_ins_Lb1->x(),90*sy,ui->m_ins_Lb1->width(),ui->m_ins_Lb1->height());
                    ui->m_ins_HP_Dsb->setFont(ff5);
                    ui->m_ins_HT_Dsb->setGeometry(ui->m_ins_Lb1->x(),210*sy,ui->m_ins_Lb1->width(),ui->m_ins_Lb1->height());
                    ui->m_ins_HT_Dsb->setFont(ff5);
                    ui->m_ins_PT_Dsb->setGeometry(ui->m_ins_Lb1->x(),330*sy,ui->m_ins_Lb1->width(),ui->m_ins_Lb1->height());
                    ui->m_ins_PT_Dsb->setFont(ff5);
                    ui->m_ins_PM_Dsb->setGeometry(ui->m_ins_Lb1->x(),450*sy,ui->m_ins_Lb1->width(),ui->m_ins_Lb1->height());
                    ui->m_ins_PM_Dsb->setFont(ff5);

                ui->m_in_Lb1->setGeometry(180*sx,20*sy,200*sx,50*sy);
                ui->m_in_Lb1->setFont(ff2);
                ui->m_in_Lb2->setGeometry(190*sx,142*sy,200*sx,30*sy);
                ui->m_in_Lb2->setFont(ff5);
                ui->m_in_Lb3->setGeometry(ui->m_in_Lb2->x(),538*sy,ui->m_in_Lb2->width(),ui->m_in_Lb2->height());
                ui->m_in_Lb3->setFont(ff5);
                ui->m_in_Lb4->setGeometry(260*sx,220*sy,300*sx,40*sy);
                ui->m_in_Lb4->setFont(ff5);
                ui->m_in_Lb5->setGeometry(ui->m_in_Lb4->x(),300*sy,ui->m_in_Lb4->width(),ui->m_in_Lb4->height());
                ui->m_in_Lb5->setFont(ff5);
                ui->m_in_Lb6->setGeometry(ui->m_in_Lb4->x(),380*sy,ui->m_in_Lb4->width(),ui->m_in_Lb4->height());
                ui->m_in_Lb6->setFont(ff5);
                ui->m_in_Lb7->setGeometry(ui->m_in_Lb4->x(),620*sy,ui->m_in_Lb4->width(),ui->m_in_Lb4->height());
                ui->m_in_Lb7->setFont(ff5);
                ui->m_in_Lb8->setGeometry(ui->m_in_Lb4->x(),700*sy,ui->m_in_Lb4->width(),ui->m_in_Lb4->height());
                ui->m_in_Lb8->setFont(ff5);
                ui->m_in_Lb9->setGeometry(ui->m_in_Lb4->x(),780*sy,ui->m_in_Lb4->width(),ui->m_in_Lb4->height());
                ui->m_in_Lb9->setFont(ff5);

                ui->m_in_OVSet_COB->setGeometry(390*sx,ui->m_in_Lb1->y(),619*sx,ui->m_in_Lb1->height());
                ui->m_in_OVSet_COB->setFont(ff2);
                ui->m_in_ChooseBtn->setGeometry(1020*sx,ui->m_in_Lb1->y(),50*sx,ui->m_in_Lb1->height());

                ui->m_in_PerigeeHigh_Dsb->setGeometry(590*sx,220*sy,255*sx,41*sy);
                ui->m_in_PerigeeHigh_Dsb->setFont(ff5);
                ui->m_in_StartEpoch_Dte->setGeometry(ui->m_in_PerigeeHigh_Dsb->x(),300*sy,391*sx,ui->m_in_PerigeeHigh_Dsb->height());
                ui->m_in_StartEpoch_Dte->setFont(ff5);
                ui->m_in_NumSpit_Dsb->setGeometry(ui->m_in_PerigeeHigh_Dsb->x(),380*sy,ui->m_in_PerigeeHigh_Dsb->width(),ui->m_in_PerigeeHigh_Dsb->height());
                ui->m_in_NumSpit_Dsb->setFont(ff5);
                ui->m_in_StartSim_Dte->setGeometry(ui->m_in_PerigeeHigh_Dsb->x(),620*sy,ui->m_in_StartEpoch_Dte->width(),ui->m_in_PerigeeHigh_Dsb->height());
                ui->m_in_StartSim_Dte->setFont(ff5);
                ui->m_in_EndSim_Dte->setGeometry(ui->m_in_PerigeeHigh_Dsb->x(),700*sy,ui->m_in_StartEpoch_Dte->width(),ui->m_in_PerigeeHigh_Dsb->height());
                ui->m_in_EndSim_Dte->setFont(ff5);
                ui->m_in_PrintStep_Dsb->setGeometry(ui->m_in_PerigeeHigh_Dsb->x(),780*sy,ui->m_in_PerigeeHigh_Dsb->width(),ui->m_in_PerigeeHigh_Dsb->height());
                ui->m_in_PrintStep_Dsb->setFont(ff5);

                //-------------Output page MAN--------------------------------------------------------------------//
                ui->page_OutputMAN->setGeometry(0,0,ui->sub_Main->width(),ui->sub_Main->height());
                ui->m_out_bg->setGeometry(0,0,ui->sub_Main->width(),ui->sub_Main->height());
                ui->m_out_H1_Lb->setGeometry(80*sx,40*sy,300*sx,40*sy);
                ui->m_out_H1_Lb->setFont(ff5);

                ui->m_out_TextBtn->setGeometry(1000*sx,44*sy,44*sx,40*sy);
                ui->m_out_GraphBtn->setGeometry(1100*sx,44*sy,41*sx,39*sy);
                ui->page_OutputMAN_TG->setGeometry(73*sx,156*sy,1212*sx,744*sy);
                ui->m_OutG->setGeometry(0,0,ui->page_OutputMAN_TG->width(),ui->page_OutputMAN_TG->height());
                ui->m_OutT->setGeometry(0,0,ui->page_OutputMAN_TG->width(),ui->page_OutputMAN_TG->height());

                    //-------------Sub Output page------------------------------------------------------------//
                    ui->page_OutputMAN_sub->setGeometry(0,0,ui->sub_Main2->width(),ui->sub_Main2->height());
                    ui->m_outs_Lb1->setGeometry(50*sx,130*sy,300*sx,40*sy);
                    ui->m_outs_Lb1->setFont(ff5);
                    ui->m_outs_Lb2->setGeometry(ui->m_outs_Lb1->x(),250*sy,ui->m_outs_Lb1->width(),ui->m_outs_Lb1->height());
                    ui->m_outs_Lb2->setFont(ff5);
                    ui->m_outs_Lb3->setGeometry(ui->m_outs_Lb1->x(),370*sy,ui->m_outs_Lb1->width(),ui->m_outs_Lb1->height());
                    ui->m_outs_Lb3->setFont(ff5);

                    ui->m_outs_Overall_Dsb->setGeometry(ui->m_outs_Lb1->x(),170*sy,ui->m_outs_Lb1->width(),ui->m_outs_Lb1->height());
                    ui->m_outs_Overall_Dsb->setFont(ff5);
                    ui->m_outs_Perigee_Dsb->setGeometry(ui->m_outs_Lb1->x(),290*sy,ui->m_outs_Lb1->width(),ui->m_outs_Lb1->height());
                    ui->m_outs_Perigee_Dsb->setFont(ff5);
                    ui->m_outs_Epoch_Dsb->setGeometry(ui->m_outs_Lb1->x(),410*sy,ui->m_outs_Lb1->width(),ui->m_outs_Lb1->height());
                    ui->m_outs_Epoch_Dsb->setFont(ff5);

                    //-------------Graph Output page------------------------------------------------------------//

                    //-------------Text Output page------------------------------------------------------------//
                    ui->m_outT_bg->setGeometry(10*sx,3*sy,1192*sx,738*sy);
                    ui->m_outT_SpoolPte->setGeometry(22*sx,15*sy,1168*sx,662*sy);
                    ui->m_outT_SpoolPte->setFont(ff7);
                    ui->m_outT_IndexS_Led->setGeometry(15*sx,705*sy,270*sx,35*sy);
                    ui->m_outT_IndexS_Led->setFont(ff7);
                    ui->m_outT_SearchBtn->setGeometry(323*sx,703*sy,77*sx,38*sy);

                //-------------Input page OTR--------------------------------------------------------------------//
                ui->page_InputOTR->setGeometry(0,0,ui->sub_Main->width(),ui->sub_Main->height());
                ui->o_in_bg->setGeometry(0,0,ui->page_InputOTR->width(),ui->page_InputOTR->height());

                ui->o_in_Lb1->setGeometry(145*sx,22*sy,300*sx,50*sy);
                ui->o_in_Lb1->setFont(ff2);
                ui->o_in_Lb2->setGeometry(130*sx,80*sy,175*sx,81*sy);
                ui->o_in_Lb2->setFont(ff5);
                ui->o_in_Lb3->setGeometry(310*sx,ui->o_in_Lb2->y(),ui->o_in_Lb2->width(),ui->o_in_Lb2->height());
                ui->o_in_Lb3->setFont(ff5);
                ui->o_in_Lb4->setGeometry(490*sx,ui->o_in_Lb2->y(),ui->o_in_Lb2->width(),ui->o_in_Lb2->height());
                ui->o_in_Lb4->setFont(ff5);
                ui->o_in_Lb5->setGeometry(770*sx,ui->o_in_Lb2->y(),ui->o_in_Lb2->width(),ui->o_in_Lb2->height());
                ui->o_in_Lb5->setFont(ff5);
                ui->o_in_Lb6->setGeometry(1060*sx,ui->o_in_Lb2->y(),ui->o_in_Lb2->width(),ui->o_in_Lb2->height());
                ui->o_in_Lb6->setFont(ff5);

                ui->sup_input->setGeometry(130*sx,170*sy,1100*sx,630*sy);

                if(m_init)
                {
                    for(int i=0;i<4;i++)
                    {
                        Num_of_OCM_list[(i*7)+1]->setGeometry(33*sx,18*sy,113*sx,45*sy);
                        Num_of_OCM_list[(i*7)+2]->setGeometry(Num_of_OCM_list[(i*7)+1]->x(),107*sy,Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_OCM_list[(i*7)+3]->setGeometry(Num_of_OCM_list[(i*7)+1]->x(),196*sy,Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_OCM_list[(i*7)+4]->setGeometry(Num_of_OCM_list[(i*7)+1]->x(),285*sy,Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_OCM_list[(i*7)+5]->setGeometry(Num_of_OCM_list[(i*7)+1]->x(),374*sy,Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_OCM_list[(i*7)+6]->setGeometry(Num_of_OCM_list[(i*7)+1]->x(),463*sy,Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_OCM_list[(i*7)+7]->setGeometry(Num_of_OCM_list[(i*7)+1]->x(),552*sy,Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());

                        TypeOCM_list[(i*7)+1]->setGeometry(214*sx,Num_of_OCM_list[(i*7)+1]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        TypeOCM_list[(i*7)+2]->setGeometry(TypeOCM_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+2]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        TypeOCM_list[(i*7)+3]->setGeometry(TypeOCM_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+3]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        TypeOCM_list[(i*7)+4]->setGeometry(TypeOCM_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+4]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        TypeOCM_list[(i*7)+5]->setGeometry(TypeOCM_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+5]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        TypeOCM_list[(i*7)+6]->setGeometry(TypeOCM_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+6]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        TypeOCM_list[(i*7)+7]->setGeometry(TypeOCM_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+7]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());

                        Num_of_Im_list[(i*7)+1]->setGeometry(393*sx,Num_of_OCM_list[(i*7)+1]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_Im_list[(i*7)+2]->setGeometry(Num_of_Im_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+2]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_Im_list[(i*7)+3]->setGeometry(Num_of_Im_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+3]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_Im_list[(i*7)+4]->setGeometry(Num_of_Im_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+4]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_Im_list[(i*7)+5]->setGeometry(Num_of_Im_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+5]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_Im_list[(i*7)+6]->setGeometry(Num_of_Im_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+6]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Num_of_Im_list[(i*7)+7]->setGeometry(Num_of_Im_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+7]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());

                        Epoch_list[(i*7)+1]->setGeometry(592*sx,Num_of_OCM_list[(i*7)+1]->y(),282*sx,Num_of_OCM_list[(i*7)+1]->height());
                        Epoch_list[(i*7)+2]->setGeometry(Epoch_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+2]->y(),Epoch_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Epoch_list[(i*7)+3]->setGeometry(Epoch_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+3]->y(),Epoch_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Epoch_list[(i*7)+4]->setGeometry(Epoch_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+4]->y(),Epoch_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Epoch_list[(i*7)+5]->setGeometry(Epoch_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+5]->y(),Epoch_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Epoch_list[(i*7)+6]->setGeometry(Epoch_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+6]->y(),Epoch_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Epoch_list[(i*7)+7]->setGeometry(Epoch_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+7]->y(),Epoch_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());

                        Delta_A_list[(i*7)+1]->setGeometry(960*sx,Num_of_OCM_list[(i*7)+1]->y(),Num_of_OCM_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Delta_A_list[(i*7)+2]->setGeometry(Delta_A_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+2]->y(),Delta_A_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Delta_A_list[(i*7)+3]->setGeometry(Delta_A_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+3]->y(),Delta_A_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Delta_A_list[(i*7)+4]->setGeometry(Delta_A_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+4]->y(),Delta_A_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Delta_A_list[(i*7)+5]->setGeometry(Delta_A_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+5]->y(),Delta_A_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Delta_A_list[(i*7)+6]->setGeometry(Delta_A_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+6]->y(),Delta_A_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                        Delta_A_list[(i*7)+7]->setGeometry(Delta_A_list[(i*7)+1]->x(),Num_of_OCM_list[(i*7)+7]->y(),Delta_A_list[(i*7)+1]->width(),Num_of_OCM_list[(i*7)+1]->height());
                    }
                    for(int i=1;i<=OCM_max;i++)
                    {
                        Num_of_OCM_list[i]->setFont(ff8);
                        TypeOCM_list[i]->setFont(ff8);
                        Num_of_Im_list[i]->setFont(ff8);
                        Epoch_list[i]->setFont(ff8);
                        Delta_A_list[i]->setFont(ff8);
                    }
                    ui->P_Btn->setGeometry(172*sx,807*sy,44*sx,44*sy);
                    ui->D_Btn->setGeometry(238*sx,ui->P_Btn->y(),ui->P_Btn->width(),ui->P_Btn->height());
                    ui->Back_Btn->setGeometry(1079*sx,ui->P_Btn->y(),ui->P_Btn->width(),ui->P_Btn->height());
                    ui->Next_Btn->setGeometry(1146*sx,ui->P_Btn->y(),ui->P_Btn->width(),ui->P_Btn->height());
                    ui->Start_Btn->setGeometry(928*sx,ui->P_Btn->y(),130*sx,ui->P_Btn->height());
                }

                    //-------------Sub Input page------------------------------------------------------------//
                    ui->page_OutputOTR_sub->setGeometry(0,0,ui->sub_Main2->width(),ui->sub_Main2->height());
                    ui->o_outs_Lb1->setGeometry(50*sx,170*sy,300*sx,40*sy);
                    ui->o_outs_Lb1->setFont(ff5);
                    ui->o_outs_Lb2->setGeometry(ui->m_outs_Lb1->x(),290*sy,ui->m_outs_Lb1->width(),ui->m_outs_Lb1->height());
                    ui->o_outs_Lb2->setFont(ff5);

                    ui->o_outs_Overall_Dsb->setGeometry(ui->m_outs_Lb1->x(),210*sy,ui->m_outs_Lb1->width(),ui->m_outs_Lb1->height());
                    ui->o_outs_Overall_Dsb->setFont(ff5);
                    ui->o_outs_NumMAN_Dsb->setGeometry(ui->m_outs_Lb1->x(),330*sy,ui->m_outs_Lb1->width(),ui->m_outs_Lb1->height());
                    ui->o_outs_NumMAN_Dsb->setFont(ff5);

                //-------------Output page OTR G --------------------------------------------------------------------//
                ui->page_OutputOTR_G->setGeometry(0,0,ui->sub_Main->width(),ui->sub_Main->height());
                ui->o_outG_bg->setGeometry(0,0,ui->page_OutputOTR_G->width(),ui->page_OutputOTR_G->height());

                ui->o_outG_H1_Lb->setGeometry(80*sx,40*sy,300*sx,40*sy);
                ui->o_outG_H1_Lb->setFont(ff2);
                ui->o_outG_SG1_Btn->setGeometry(466*sx,1*sy,127*sx,121*sy);
                ui->o_outG_SG1_Btn->setFont(ff2);
                ui->o_outG_SG2_Btn->setGeometry(592*sx,ui->o_outG_SG1_Btn->y(),ui->o_outG_SG1_Btn->width(),ui->o_outG_SG1_Btn->height());
                ui->o_outG_SG2_Btn->setFont(ff2);
                ui->o_outG_SG3_Btn->setGeometry(718*sx,ui->o_outG_SG1_Btn->y(),ui->o_outG_SG1_Btn->width(),ui->o_outG_SG1_Btn->height());
                ui->o_outG_SG3_Btn->setFont(ff2);
                ui->o_outG_SG4_Btn->setGeometry(844*sx,ui->o_outG_SG1_Btn->y(),128*sx,ui->o_outG_SG1_Btn->height());
                ui->o_outG_SG4_Btn->setFont(ff2);
                ui->o_outG_SG5_Btn->setGeometry(971*sx,ui->o_outG_SG1_Btn->y(),ui->o_outG_SG1_Btn->width(),ui->o_outG_SG1_Btn->height());
                ui->o_outG_SG5_Btn->setFont(ff2);

                ui->o_outG_TextBtn->setGeometry(1150*sx,40*sy,44*sx,40*sy);
                ui->o_outG_GraphBtn->setGeometry(1250*sx,40*sy,41*sx,39*sy);

                    //-------------Sub Output G page------------------------------------------------------------//
                    ui->sub_OutG_OTR->setGeometry(78*sx,161*sy,1201*sx,734*sy);
                    ui->o_outG_p1->setGeometry(0,0,ui->sub_OutG_OTR->width(),ui->sub_OutG_OTR->height());
                    ui->o_outG_p2->setGeometry(0,0,ui->sub_OutG_OTR->width(),ui->sub_OutG_OTR->height());
                    ui->o_outG_p3->setGeometry(0,0,ui->sub_OutG_OTR->width(),ui->sub_OutG_OTR->height());
                    ui->o_outG_p4->setGeometry(0,0,ui->sub_OutG_OTR->width(),ui->sub_OutG_OTR->height());
                    ui->o_outG_p5->setGeometry(0,0,ui->sub_OutG_OTR->width(),ui->sub_OutG_OTR->height());

                //-------------Output page OTR T --------------------------------------------------------------------//
                ui->page_OutputOTR_T->setGeometry(0,0,ui->sub_Main->width(),ui->sub_Main->height());
                ui->o_outT_bg->setGeometry(0,0,ui->page_OutputOTR_G->width(),ui->page_OutputOTR_G->height());

                ui->o_outT_H1_Lb->setGeometry(80*sx,40*sy,300*sx,40*sy);
                ui->o_outT_H1_Lb->setFont(ff2);
                ui->o_outT_SG1_Btn->setGeometry(606*sx,1*sy,165*sx,121*sy);
                ui->o_outT_SG1_Btn->setFont(ff2);
                ui->o_outT_SG2_Btn->setGeometry(770*sx,ui->o_outT_SG1_Btn->y(),ui->o_outT_SG1_Btn->width(),ui->o_outT_SG1_Btn->height());
                ui->o_outT_SG2_Btn->setFont(ff2);
                ui->o_outT_SG3_Btn->setGeometry(933*sx,ui->o_outT_SG1_Btn->y(),ui->o_outT_SG1_Btn->width(),ui->o_outT_SG1_Btn->height());
                ui->o_outT_SG3_Btn->setFont(ff2);

                ui->o_outT_TextBtn->setGeometry(1150*sx,40*sy,44*sx,40*sy);
                ui->o_outT_GraphBtn->setGeometry(1250*sx,40*sy,41*sx,39*sy);
                ui->o_outT_IndexS_Led->setGeometry(87*sx,860*sy,270*sx,35*sy);
                ui->o_outT_IndexS_Led->setFont(ff7);
                ui->o_outT_SearchBtn->setGeometry(395*sx,858*sy,77*sx,38*sy);

                    //-------------Sub Output T page------------------------------------------------------------//
                    ui->sub_OutT_OTR->setGeometry(94*sx,170*sy,1168*sx,662*sy);
                    ui->o_outG_p1->setGeometry(0,0,ui->sub_OutT_OTR->width(),ui->sub_OutT_OTR->height());
                    ui->o_outT_PlanPte->setGeometry(0,0,ui->o_outG_p1->width(),ui->o_outG_p1->height());
                    ui->o_outT_PlanPte->setFont(ff7);
                    ui->o_outG_p2->setGeometry(0,0,ui->sub_OutT_OTR->width(),ui->sub_OutT_OTR->height());
                    ui->o_outT_PassPte->setGeometry(0,0,ui->o_outG_p2->width(),ui->o_outG_p2->height());
                    ui->o_outT_PassPte->setFont(ff7);
                    ui->o_outG_p3->setGeometry(0,0,ui->sub_OutT_OTR->width(),ui->sub_OutT_OTR->height());
                    ui->o_outT_SpoolPte->setGeometry(0,0,ui->o_outG_p3->width(),ui->o_outG_p3->height());
                    ui->o_outT_SpoolPte->setFont(ff7);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Update_CurrentTime()
{
    ui->st_TimeDisplay_Lb->setText(QDateTime::currentDateTimeUtc().toString("hh:mm"));
    ui->m_TimeDisplay_Lb->setText(QDateTime::currentDateTimeUtc().toString("hh:mm"));
}
//----------------------------------------------------------------------------------------------------------//
void DOS::keyReleaseEvent(QKeyEvent *key)
{
//    if(key->text() == "*")
//    {
//        if(ui->m_in_StartEpoch_Dte->isActiveWindow())
//        {
//            fs.ClearTimeZero(ui->m_in_StartEpoch_Dte);
//        }
//        else if(ui->m_in_StartSim_Dte->isActiveWindow())
//        {

//        }
//        else if(ui->m_in_EndSim_Dte->isActiveWindow())
//        {

//        }
//        else if(ui->m_outs_Epoch_Dsb->isActiveWindow())
//        {

//        }
//    }
}
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
//-------------------------------------> Service Function <-------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
void DOS::Init()
{
    //------------------ Set Parameter Default -------------------------------------------------------------//
    m_parent = 0;
    m_menu = 1;
    m_process = 0;
    m_page = 1;
    m_Mode = 0;
    sx = 1;
    sy = 1;

    num = 0;

    OCM_count = 0;
    OCM_max = 28;

    spool = "";
    pahtFM = "C:\\FDS_Operation\\System\\dos";
    pahtIM = ":/Image/DOS";

    //------------------ Set Page Default ------------------------------------------------------------------//
    ui->SW->setCurrentIndex(1);
    ui->sub_Main->setCurrentIndex(0);
    ui->sub_Main2->setCurrentIndex(0);

    //------------------set Item----------------------------------------------------------------------------//
    Num_of_OCM_list << ui->Num_of_OCM_1;
    Num_of_OCM_list << ui->Num_of_OCM_1;
    Num_of_OCM_list << ui->Num_of_OCM_2;
    Num_of_OCM_list << ui->Num_of_OCM_3;
    Num_of_OCM_list << ui->Num_of_OCM_4;
    Num_of_OCM_list << ui->Num_of_OCM_5;
    Num_of_OCM_list << ui->Num_of_OCM_6;
    Num_of_OCM_list << ui->Num_of_OCM_7;
    Num_of_OCM_list << ui->Num_of_OCM_8;
    Num_of_OCM_list << ui->Num_of_OCM_9;
    Num_of_OCM_list << ui->Num_of_OCM_10;
    Num_of_OCM_list << ui->Num_of_OCM_11;
    Num_of_OCM_list << ui->Num_of_OCM_12;
    Num_of_OCM_list << ui->Num_of_OCM_13;
    Num_of_OCM_list << ui->Num_of_OCM_14;
    Num_of_OCM_list << ui->Num_of_OCM_15;
    Num_of_OCM_list << ui->Num_of_OCM_16;
    Num_of_OCM_list << ui->Num_of_OCM_17;
    Num_of_OCM_list << ui->Num_of_OCM_18;
    Num_of_OCM_list << ui->Num_of_OCM_19;
    Num_of_OCM_list << ui->Num_of_OCM_20;
    Num_of_OCM_list << ui->Num_of_OCM_21;
    Num_of_OCM_list << ui->Num_of_OCM_22;
    Num_of_OCM_list << ui->Num_of_OCM_23;
    Num_of_OCM_list << ui->Num_of_OCM_24;
    Num_of_OCM_list << ui->Num_of_OCM_25;
    Num_of_OCM_list << ui->Num_of_OCM_26;
    Num_of_OCM_list << ui->Num_of_OCM_27;
    Num_of_OCM_list << ui->Num_of_OCM_28;

    Num_of_Im_list << ui->Num_of_Im_1;
    Num_of_Im_list << ui->Num_of_Im_1;
    Num_of_Im_list << ui->Num_of_Im_2;
    Num_of_Im_list << ui->Num_of_Im_3;
    Num_of_Im_list << ui->Num_of_Im_4;
    Num_of_Im_list << ui->Num_of_Im_5;
    Num_of_Im_list << ui->Num_of_Im_6;
    Num_of_Im_list << ui->Num_of_Im_7;
    Num_of_Im_list << ui->Num_of_Im_8;
    Num_of_Im_list << ui->Num_of_Im_9;
    Num_of_Im_list << ui->Num_of_Im_10;
    Num_of_Im_list << ui->Num_of_Im_11;
    Num_of_Im_list << ui->Num_of_Im_12;
    Num_of_Im_list << ui->Num_of_Im_13;
    Num_of_Im_list << ui->Num_of_Im_14;
    Num_of_Im_list << ui->Num_of_Im_15;
    Num_of_Im_list << ui->Num_of_Im_16;
    Num_of_Im_list << ui->Num_of_Im_17;
    Num_of_Im_list << ui->Num_of_Im_18;
    Num_of_Im_list << ui->Num_of_Im_19;
    Num_of_Im_list << ui->Num_of_Im_20;
    Num_of_Im_list << ui->Num_of_Im_21;
    Num_of_Im_list << ui->Num_of_Im_22;
    Num_of_Im_list << ui->Num_of_Im_23;
    Num_of_Im_list << ui->Num_of_Im_24;
    Num_of_Im_list << ui->Num_of_Im_25;
    Num_of_Im_list << ui->Num_of_Im_26;
    Num_of_Im_list << ui->Num_of_Im_27;
    Num_of_Im_list << ui->Num_of_Im_28;

    TypeOCM_list << ui->TypeOCM_1;
    TypeOCM_list << ui->TypeOCM_1;
    TypeOCM_list << ui->TypeOCM_2;
    TypeOCM_list << ui->TypeOCM_3;
    TypeOCM_list << ui->TypeOCM_4;
    TypeOCM_list << ui->TypeOCM_5;
    TypeOCM_list << ui->TypeOCM_6;
    TypeOCM_list << ui->TypeOCM_7;
    TypeOCM_list << ui->TypeOCM_8;
    TypeOCM_list << ui->TypeOCM_9;
    TypeOCM_list << ui->TypeOCM_10;
    TypeOCM_list << ui->TypeOCM_11;
    TypeOCM_list << ui->TypeOCM_12;
    TypeOCM_list << ui->TypeOCM_13;
    TypeOCM_list << ui->TypeOCM_14;
    TypeOCM_list << ui->TypeOCM_15;
    TypeOCM_list << ui->TypeOCM_16;
    TypeOCM_list << ui->TypeOCM_17;
    TypeOCM_list << ui->TypeOCM_18;
    TypeOCM_list << ui->TypeOCM_19;
    TypeOCM_list << ui->TypeOCM_20;
    TypeOCM_list << ui->TypeOCM_21;
    TypeOCM_list << ui->TypeOCM_22;
    TypeOCM_list << ui->TypeOCM_23;
    TypeOCM_list << ui->TypeOCM_24;
    TypeOCM_list << ui->TypeOCM_25;
    TypeOCM_list << ui->TypeOCM_26;
    TypeOCM_list << ui->TypeOCM_27;
    TypeOCM_list << ui->TypeOCM_28;

    Epoch_list << ui->Epoch_1;
    Epoch_list << ui->Epoch_1;
    Epoch_list << ui->Epoch_2;
    Epoch_list << ui->Epoch_3;
    Epoch_list << ui->Epoch_4;
    Epoch_list << ui->Epoch_5;
    Epoch_list << ui->Epoch_6;
    Epoch_list << ui->Epoch_7;
    Epoch_list << ui->Epoch_8;
    Epoch_list << ui->Epoch_9;
    Epoch_list << ui->Epoch_10;
    Epoch_list << ui->Epoch_11;
    Epoch_list << ui->Epoch_12;
    Epoch_list << ui->Epoch_13;
    Epoch_list << ui->Epoch_14;
    Epoch_list << ui->Epoch_15;
    Epoch_list << ui->Epoch_16;
    Epoch_list << ui->Epoch_17;
    Epoch_list << ui->Epoch_18;
    Epoch_list << ui->Epoch_19;
    Epoch_list << ui->Epoch_20;
    Epoch_list << ui->Epoch_21;
    Epoch_list << ui->Epoch_22;
    Epoch_list << ui->Epoch_23;
    Epoch_list << ui->Epoch_24;
    Epoch_list << ui->Epoch_25;
    Epoch_list << ui->Epoch_26;
    Epoch_list << ui->Epoch_27;
    Epoch_list << ui->Epoch_28;

    Delta_A_list << ui->Delta_A_1;
    Delta_A_list << ui->Delta_A_1;
    Delta_A_list << ui->Delta_A_2;
    Delta_A_list << ui->Delta_A_3;
    Delta_A_list << ui->Delta_A_4;
    Delta_A_list << ui->Delta_A_5;
    Delta_A_list << ui->Delta_A_6;
    Delta_A_list << ui->Delta_A_7;
    Delta_A_list << ui->Delta_A_8;
    Delta_A_list << ui->Delta_A_9;
    Delta_A_list << ui->Delta_A_10;
    Delta_A_list << ui->Delta_A_11;
    Delta_A_list << ui->Delta_A_12;
    Delta_A_list << ui->Delta_A_13;
    Delta_A_list << ui->Delta_A_14;
    Delta_A_list << ui->Delta_A_15;
    Delta_A_list << ui->Delta_A_16;
    Delta_A_list << ui->Delta_A_17;
    Delta_A_list << ui->Delta_A_18;
    Delta_A_list << ui->Delta_A_19;
    Delta_A_list << ui->Delta_A_20;
    Delta_A_list << ui->Delta_A_21;
    Delta_A_list << ui->Delta_A_22;
    Delta_A_list << ui->Delta_A_23;
    Delta_A_list << ui->Delta_A_24;
    Delta_A_list << ui->Delta_A_25;
    Delta_A_list << ui->Delta_A_26;
    Delta_A_list << ui->Delta_A_27;
    Delta_A_list << ui->Delta_A_28;

    //------------------------ Set Icon State --------------------------------------------------------------//
    Icon_Down.addFile(pahtIM+"/me_down.png", QSize(), QIcon::Normal, QIcon::Off);
    Icon_Up.addFile(pahtIM+"/me_up.png", QSize(), QIcon::Normal, QIcon::Off);

    //------------------------ Set StyleSheet State --------------------------------------------------------//
    bg_ok_off = "QPushButton{border-image: url(:/Image/Main/icon_icon.png);color: rgb(18, 5, 51);}QPushButton:hover{border-image: url(:/Image/DOS/st_ok_se.png);color: rgb(241, 242, 242);}";
    bg_ok_on = "border-image: url(:/Image/DOS/st_ok_se.png);color: rgb(241, 242, 242);";

    bg_setMode_on = "border-image: url(:/Image/DOS/st_frame_se.png);color: rgb(241, 242, 242);";
    bg_setMode_off = "border-image: url(:/Image/Main/icon_icon.png);color: rgb(18, 5, 51);";

    bg_Start_off = "QPushButton{border-image: url(:/Image/DOS/m_in_start.png);}QPushButton:Hover{border-image: url(:/Image/DOS/m_in_start_se.png);}";
    bg_Start_on = "border-image: url(:/Image/DOS/m_in_start_se.png);";

    bg_Run_off = "QPushButton:Hover{border-image: url(:/Image/DOS/o_in_run_se.png);}";
    bg_Run_on = "border-image: url(:/Image/DOS/o_in_run_se.png);";

    bg_Graph_off = "QPushButton{border-image: url(:/Image/DOS/m_out_icon_graph.png);}QPushButton:Hover{border-image: url(:/Image/DOS/m_out_icon_graph_se.png);}";
    bg_Graph_on = "border-image: url(:/Image/DOS/m_out_icon_graph_se.png);";

    bg_Text_off = "QPushButton{border-image: url(:/Image/DOS/m_out_icon_input.png);}QPushButton:Hover{border-image: url(:/Image/DOS/m_out_icon_input_se.png);}";
    bg_Text_on = "border-image: url(:/Image/DOS/m_out_icon_input_se.png);";

    bg_point_on = "border-image: url(:/Image/DOS/m_in_page_se.png);";
    bg_point_off = "border-image: url(:/Image/DOS/m_in_page.png);";

    bg_sent_off = "QPushButton{border-image: url(:/Image/DOS/sent.png);}QPushButton:Hover{border-image: url(:/Image/DOS/sent_se.png);}";
    bg_sent_on = "border-image: url(:/Image/DOS/sent_se.png);";

    bg_save_off = "QPushButton{border-image: url(:/Image/DOS/save.png);}QPushButton:Hover{border-image: url(:/Image/DOS/save_se.png);}";
    bg_save_on = "border-image: url(:/Image/DOS/save_se.png);";

    bg_print_off = "QPushButton{border-image: url(:/Image/DOS/print.png);}QPushButton:Hover{border-image: url(:/Image/DOS/print_se.png);}";
    bg_print_on = "border-image: url(:/Image/DOS/print_se.png);";

    bg_archive_off = "QPushButton{border-image: url(:/Image/DOS/archive.png);}QPushButton:Hover{border-image: url(:/Image/DOS/archive_se.png);}";
    bg_archive_on = "border-image: url(:/Image/DOS/archive_se.png);";

    bg_GSGBtn_on = "border-image: url(:/Image/DOS/o_outG_frame_se.png);color: rgb(65, 64,66);";
    bg_GSGBtn_off = "QPushButton{color: rgb(175, 206, 206);}QPushButton:Hover{border-image: url(:/Image/DOS/o_outG_frame_se.png);color: rgb(65, 64,66);}";

    bg_TSGBtn_on = "border-image: url(:/Image/DOS/o_outT_frame_se.png);color: rgb(65, 64,66);";
    bg_TSGBtn_off = "QPushButton{color: rgb(175, 206, 206);}QPushButton:Hover{border-image: url(:/Image/DOS/o_outT_frame_se.png);color: rgb(65, 64,66);}";

    //------------------------ Init Function ---------------------------------------------------------------//
    Input_State(1,0);
    LoadDetail();

    //----------------------- Set State Default ------------------------------------------------------------//
    OCM_count = 1;
    this->Input_State(0,OCM_count);
    okBtn_State(0);
    Menu_State(1);
    GSGBtn_State(1);
    TSGBtn_State(1);
    on_sup_setting_currentChanged(0);
    m_init = 1;
}
//----------------------------------------------------------------------------------------------------------//
void DOS::LoadDefault()
{
    QString ms = "";
    spool += "\n\n>> Startup : OCM Configuration";
    spool += "\n   Load : Setting config --- Format Version : -1";
    //-----------------------load OCM_CONFIG----------------------------------------------------------------//
    if(!fs.Load_OCM_Config(pahtFM+"\\OCM_CONFIG.txt",OCset,spool,ms))
    {
        ui->SV_QDS_1->setValue(OCset.K0);
        ui->SV_QDS_2->setValue(OCset.K1);
        ui->SV_QDS_3->setValue(OCset.K2);
        ui->SV_QDS_4->setValue(OCset.K3);
        ui->SV_QDS_5->setValue(OCset.K4);
        ui->SV_QDS_6->setValue(OCset.K5);
        ui->SV_QDS_7->setValue(OCset.K6);
        ui->SV_QDS_8->setValue(OCset.K7);
        ui->SV_QDS_9->setValue(OCset.K8);
        ui->SV_QDS_10->setValue(OCset.K9);
        ui->SV_QDS_11->setValue(OCset.K10);
        ui->SV_QDS_12->setValue(OCset.K11);
        ui->SV_QDS_13->setValue(OCset.K12);
        ui->SV_QDS_14->setValue(OCset.K13);
        ui->SV_QDS_15->setValue(OCset.K14);
        ui->SV_QDS_16->setValue(OCset.K15);
        ui->SV_QDS_17->setValue(OCset.K16);
        ui->SV_QDS_18->setValue(OCset.K17);
        ui->SV_QDS_19->setValue(OCset.K18);
        ui->SV_QDS_20->setValue(OCset.K19);
        ui->SV_QDS_21->setValue(OCset.K20);
        ui->SV_QDS_22->setValue(OCset.K21);
        ui->SV_QDS_23->setValue(OCset.K22);
        ui->SV_QDS_24->setValue(OCset.K23);
        ui->SV_QDS_25->setValue(OCset.K24);
        ui->SV_QDS_26->setValue(OCset.K25);
        ui->SV_QDS_27->setValue(OCset.K26);
        ui->SV_QDS_28->setValue(OCset.K27);
        ui->SV_QDS_29->setValue(OCset.K28);
        ui->SV_QDS_30->setValue(OCset.K29);
        ui->SV_QDS_31->setValue(OCset.K30);
        ui->SV_QDS_32->setValue(OCset.K31);
        ui->SV_QDS_33->setValue(OCset.K32);
        ui->SV_QDS_34->setValue(OCset.K33);
        ui->SV_QDS_35->setValue(OCset.K34);
        ui->SV_QDS_36->setValue(OCset.K35);
        ui->SV_QDS_37->setValue(OCset.K36);
        ui->SV_QDS_38->setValue(OCset.K37);
        ui->SV_QDS_39->setValue(OCset.K38);

        ui->SV_QDS_41->setValue(OCset.C0);
        ui->SV_QDS_42->setValue(OCset.C1);
        ui->SV_QDS_43->setValue(OCset.C2);
        ui->SV_QDS_44->setValue(OCset.C3);
        ui->SV_QDS_45->setValue(OCset.C4);
        ui->SV_QDS_46->setValue(OCset.C5);
        ui->SV_QDS_47->setValue(OCset.C6);
        ui->SV_QDS_48->setValue(OCset.C7);
        ui->SV_QDS_49->setValue(OCset.C8);
        ui->SV_QDS_50->setValue(OCset.C9);

        ui->SV_QDS_51->setValue(OCset.M0);
        ui->SV_QDS_52->setValue(OCset.M1);
        ui->SV_QDS_53->setValue(OCset.M2);
        ui->SV_QDS_54->setValue(OCset.M3);
        ui->SV_QDS_55->setValue(OCset.M4);
        ui->SV_QDS_56->setValue(OCset.M5);
        ui->SV_QDS_57->setValue(OCset.M6);
        ui->SV_QDS_58->setValue(OCset.M7);

        ui->SV_QDS_61->setValue(OCset.U0);
        ui->SV_QDS_62->setValue(OCset.U1);
        ui->SV_QDS_63->setValue(OCset.U2);
        ui->SV_QDS_64->setValue(OCset.U3);
        ui->SV_QDS_65->setValue(OCset.U4);
        ui->SV_QDS_66->setValue(OCset.U5);

        if(OCset.F0 == "THR24")ui->SV_QDS_68->setCurrentIndex(1);
        else ui->SV_QDS_68->setCurrentIndex(0);
        if(OCset.F1 == "3_WHEELS")ui->SV_QDS_69->setCurrentIndex(1);
        else ui->SV_QDS_69->setCurrentIndex(0);
        if(OCset.F2 == "INV")ui->SV_QDS_70->setCurrentIndex(1);
        else ui->SV_QDS_70->setCurrentIndex(0);
    }
    //-----------------------load OCM_IN--------------------------------------------------------------------//
    if(!fs.Load_OCM_IND(pahtFM+"\\OCM_IN.txt",OISet,spool,ms))
    {
        ui->m_in_PerigeeHigh_Dsb->setValue(OISet.Perigee_High);
        ui->m_in_StartEpoch_Dte->setDateTime(OISet.Execut_Time);
        ui->m_in_NumSpit_Dsb->setValue(OISet.Num_of_Split);
        ui->m_ins_HP_Dsb->setValue(OISet.Helium_Pressure);
        ui->m_ins_HT_Dsb->setValue(OISet.Helium_Temperature);
        ui->m_ins_PT_Dsb->setValue(OISet.Propellant_Temperature);
        ui->m_ins_PM_Dsb->setValue(OISet.Propellant_Mass);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::LoadDetail()
{
    spool += "EMERALD : De-Orbit Simulation [" + fs.DateTime2Text() +"]";
    spool += "\n\n>> System";
    spool += "\n   Main : Emerald --- Version : -1.0";
    spool += "\n   Module : De-Orbit Simulation --- Version : -1.0";
    spool += "\n   Satellite : THEOS";

    fs.LoadOrbit(ui->m_in_OVSet_COB);
    fs.AddVector(ui->m_in_OVSet_COB->currentText(),OVSet,spool,1);
    this->LoadDefault();
    ui->Epoch_1->setDateTime(ui->m_in_StartEpoch_Dte->dateTime());
    connect(ui->m_in_OVSet_COB, SIGNAL(currentIndexChanged(int)), this, SLOT(ChVector()));

    ui->m_outT_SpoolPte->setPlainText(spool);
    ui->o_outT_SpoolPte->setPlainText(spool);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::ChVector()
{
    fs.AddVector(ui->m_in_OVSet_COB->currentText(),OVSet,spool,0);
    ui->m_outT_SpoolPte->setPlainText(spool);
    ui->o_outT_SpoolPte->setPlainText(spool);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::UpdateTemplate()
{
    dataTemplate.User = "Naluhya Yu";
    dataTemplate.Orbit_V = ui->m_in_OVSet_COB->currentText();
    dataTemplate.Perigee_High = ui->m_in_PerigeeHigh_Dsb->value();
    dataTemplate.Start_Epoch = ui->m_in_StartEpoch_Dte->dateTime();
    dataTemplate.Num_of_SpitMAN = ui->m_in_NumSpit_Dsb->value();

    dataTemplate.Start_Simulation = ui->m_in_StartSim_Dte->dateTime();
    dataTemplate.End_Simulation = ui->m_in_EndSim_Dte->dateTime();
    dataTemplate.Print_Step = ui->m_in_PrintStep_Dsb->value();

    dataTemplate.Helium_pres = ui->m_ins_HP_Dsb->value();
    dataTemplate.Helium_temp = ui->m_ins_HT_Dsb->value();
    dataTemplate.Prop_temp = ui->m_ins_PT_Dsb->value();
    dataTemplate.Prop_mass = ui->m_ins_PM_Dsb->value();

    dataTemplate.PerigeeOverall = ui->m_outs_Overall_Dsb->value();
    dataTemplate.PerigeeMAN = ui->m_outs_Perigee_Dsb->value();

    for(int i=1;i<=OCM_count;i++)
    {
        dataTemplate.OCM[i] = Num_of_OCM_list[i]->text();
        dataTemplate.Type[i] = TypeOCM_list[i]->currentText().section(' ',-1);
        dataTemplate.Num_of_imp[i] = Num_of_Im_list[i]->value();
        dataTemplate.Epoch[i] = Epoch_list[i]->text();
        dataTemplate.Delta_rp[i] = Delta_A_list[i]->value();
    }
    dataTemplate.PerigeeOverall_OTR = ui->o_outs_Overall_Dsb->value();
    dataTemplate.Num_of_MAN_OTR = ui->o_outs_NumMAN_Dsb->value();

    emit update_Template(dataTemplate);
}
//----------------------------------------------------------------------------------------------------------//
bool DOS::CreatePlot()
{
    return 0;
}
//----------------------------------------------------------------------------------------------------------//
bool DOS::CreateReport()
{
    QFile file(pahtFM + "\\emeraldout_ocmplan.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        spool += "\n   ++Error Output : OCM Plan";
        return(1);
    }
    else
    {
        QTextStream in(&file);
        ui->o_outT_PlanPte->setPlainText(in.readAll());
        file.close();
    }
    QFile file1(pahtFM + "\\sat_pass.txt");
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        spool += "\n   ++Error Output : OCM Pass";
        return(1);
    }
    else
    {
        QTextStream in1(&file1);
        ui->o_outT_PassPte->setPlainText(in1.readAll());
        file1.close();
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------------//
bool DOS::outToDir(QString paht)
{
    QDir dirA(paht);
    if(dirA.exists()){if(!dirA.removeRecursively())return(1);}
    else if(!dirA.mkpath("."))return(1);

    //------------------emeraldout_eclipse-------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_eclipse.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_eclipse.txt", paht + "\\emeraldout_eclipse.txt"))return(1);
    //------------------emeraldout_elems---------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_elems.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_elems.txt", paht + "\\emeraldout_elems.txt"))return(1);
    //------------------emeraldout_eqgterr-------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_eqgterr.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_eqgterr.txt", paht + "\\emeraldout_eqgterr.txt"))return(1);
    //------------------emeraldout_events--------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_events.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_events.txt", paht + "\\emeraldout_events.txt"))return(1);
    //------------------emeraldout_meanelms------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_meanelms.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_meanelms.txt", paht + "\\emeraldout_meanelms.txt"))return(1);
    //------------------emeraldout_nodecross-----------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_nodecross.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_nodecross.txt", paht + "\\emeraldout_nodecross.txt"))return(1);
    //------------------emeraldout_ocmcheck------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_ocmcheck.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_ocmcheck.txt", paht + "\\emeraldout_ocmcheck.txt"))return(1);
    //------------------emeraldout_ocmlog--------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_ocmlog.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_ocmlog.txt", paht + "\\emeraldout_ocmlog.txt"))return(1);
    //------------------emeraldout_ocmplan-------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_ocmplan.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_ocmplan.txt", paht + "\\emeraldout_ocmplan.txt"))return(1);
    //------------------emeraldout_plot----------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_plot.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_plot.txt", paht + "\\emeraldout_plot.txt"))return(1);
    //------------------emeraldout_pv------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_pv.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_pv.txt", paht + "\\emeraldout_pv.txt"))return(1);
    //------------------emeraldout_riset--------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_riset.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_riset.txt", paht + "\\emeraldout_riset.txt"))return(1);
    //------------------emeraldout_sk-----------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_sk.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_sk.txt", paht + "\\emeraldout_sk.txt"))return(1);
    //------------------GPS_TLE-----------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\emeraldout_sk.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\emeraldout_sk.txt", paht + "\\emeraldout_sk.txt"))return(1);
    //------------------OCM_IN------------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\OCM_IN.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\OCM_IN.txt", paht + "\\OCM_IN.txt"))return(1);
    //------------------ocm_plan1---------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\ocm_plan1.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\ocm_plan1.txt", paht + "\\ocm_plan1.txt"))return(1);
    //------------------ORBTRAN_IN--------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\ORBTRAN_IN.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\ORBTRAN_IN.txt", paht + "\\ORBTRAN_IN.txt"))return(1);
    //------------------OV_TLE------------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\OV_TLE.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\OV_TLE.txt", paht + "\\OV_TLE.txt"))return(1);
    //------------------OVSET-------------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\OVSET.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\OVSET.txt", paht + "\\OVSET.txt"))return(1);
    //------------------sat_pass----------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\sat_pass.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\sat_pass.txt", paht + "\\sat_pass.txt"))return(1);
    //------------------ORBPRO_DEF--------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\ORBPRO_DEF.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\ORBPRO_DEF.txt", paht + "\\ORBPRO_DEF.txt"))return(1);
    //------------------OCM_CONFIG--------------------------------------------------------------------------//
    if(!QFile::exists(pahtFM + "\\OCM_CONFIG.txt"))return(1);
    else if(!QFile::copy(pahtFM + "\\OCM_CONFIG.txt", paht + "\\OCM_CONFIG.txt"))return(1);

    return(0);
}
//----------------------------------------------------------------------------------------------------------//
bool DOS::Check_InputPlan()
{
    if(Delta_A_list[1]->value() <= 0)return(1);
    for(int i=2;i<=OCM_count;i++)
    {
        if(fs.DateTime2jday(Epoch_list[i]) < fs.DateTime2jday(Epoch_list[i-1]))return(1);
        if(Delta_A_list[i]->value() <= 0)return(1);
    }
    return(0);
}
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
//-------------------------------------> Action Function <--------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
void DOS::on_MinimizeBtn_clicked()
{
    if(!m_parent)this->showMinimized();
    tp->showMinimized();
    emit on_MinimizeBtn();
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_FullscreenBtn_clicked()
{
    if(!this->isFullScreen())
    {
        if(!m_parent)this->showFullScreen();
        tp->showFullScreen();
    }
    else
    {
        if(!m_parent)this->showNormal();
        tp->showNormal();
    }
    emit on_FullscreenBtn();
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_ExitBtn_clicked()
{
    this->close();
    tp->close();
    emit on_Exit();
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_setPgBtn_1_clicked()
{
    ui->sup_setting->setCurrentIndex(0);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_setPgBtn_2_clicked()
{
    ui->sup_setting->setCurrentIndex(4);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_setPgBtn_3_clicked()
{
    ui->sup_setting->setCurrentIndex(5);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_setPgBtn_4_clicked()
{
    ui->sup_setting->setCurrentIndex(6);
}
//----------------------------------------------------------------------------------------------------------//

void DOS::on_setBackBtn_clicked()
{
    if(ui->sup_setting->currentIndex() <= 0)
    {
        ui->sup_setting->setCurrentIndex(ui->sup_setting->count()-1);
    }else
        {
            ui->sup_setting->setCurrentIndex(ui->sup_setting->currentIndex() - 1);
        }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_setNextBtn_clicked()
{
    if(ui->sup_setting->currentIndex() >= (ui->sup_setting->count()-1))
    {
        ui->sup_setting->setCurrentIndex(0);
    }else
        {
            ui->sup_setting->setCurrentIndex(ui->sup_setting->currentIndex() + 1);
        }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_setOKBtn_clicked()
{
    okBtn_State(1);
    GMessage *mb = new GMessage(this);
    mb->setMessage("Are you certain that you want \nto Update Parameter on OCM Config?",0);

    if(mb->exec())
    {
        GMessage *mm = new GMessage(this);
        QString ms = "";
        spool += "\n   Save : Setting config --- Format Version : -1";

        OCset.K0 = ui->SV_QDS_1->value();
        OCset.K1 = ui->SV_QDS_2->value();
        OCset.K2 = ui->SV_QDS_3->value();
        OCset.K3 = ui->SV_QDS_4->value();
        OCset.K4 = ui->SV_QDS_5->value();
        OCset.K5 = ui->SV_QDS_6->value();
        OCset.K6 = ui->SV_QDS_7->value();
        OCset.K7 = ui->SV_QDS_8->value();
        OCset.K8 = ui->SV_QDS_9->value();
        OCset.K9 = ui->SV_QDS_10->value();
        OCset.K10 = ui->SV_QDS_11->value();
        OCset.K11 = ui->SV_QDS_12->value();
        OCset.K12 = ui->SV_QDS_13->value();
        OCset.K13 = ui->SV_QDS_14->value();
        OCset.K14 = ui->SV_QDS_15->value();
        OCset.K15 = ui->SV_QDS_16->value();
        OCset.K16 = ui->SV_QDS_17->value();
        OCset.K17 = ui->SV_QDS_18->value();
        OCset.K18 = ui->SV_QDS_19->value();
        OCset.K19 = ui->SV_QDS_20->value();
        OCset.K20 = ui->SV_QDS_21->value();
        OCset.K21 = ui->SV_QDS_22->value();
        OCset.K22 = ui->SV_QDS_23->value();
        OCset.K23 = ui->SV_QDS_24->value();
        OCset.K24 = ui->SV_QDS_25->value();
        OCset.K25 = ui->SV_QDS_26->value();
        OCset.K26 = ui->SV_QDS_27->value();
        OCset.K27 = ui->SV_QDS_28->value();
        OCset.K28 = ui->SV_QDS_29->value();
        OCset.K29 = ui->SV_QDS_30->value();
        OCset.K30 = ui->SV_QDS_31->value();
        OCset.K31 = ui->SV_QDS_32->value();
        OCset.K32 = ui->SV_QDS_33->value();
        OCset.K33 = ui->SV_QDS_34->value();
        OCset.K34 = ui->SV_QDS_35->value();
        OCset.K35 = ui->SV_QDS_36->value();
        OCset.K36 = ui->SV_QDS_37->value();
        OCset.K37 = ui->SV_QDS_38->value();
        OCset.K38 = ui->SV_QDS_39->value();

        OCset.C0 = ui->SV_QDS_41->value();
        OCset.C1 = ui->SV_QDS_42->value();
        OCset.C2 = ui->SV_QDS_43->value();
        OCset.C3 = ui->SV_QDS_44->value();
        OCset.C4 = ui->SV_QDS_45->value();
        OCset.C5 = ui->SV_QDS_46->value();
        OCset.C6 = ui->SV_QDS_47->value();
        OCset.C7 = ui->SV_QDS_48->value();
        OCset.C8 = ui->SV_QDS_49->value();
        OCset.C9 = ui->SV_QDS_50->value();

        OCset.M0 = ui->SV_QDS_51->value();
        OCset.M1 = ui->SV_QDS_52->value();
        OCset.M2 = ui->SV_QDS_53->value();
        OCset.M3 = ui->SV_QDS_54->value();
        OCset.M4 = ui->SV_QDS_55->value();
        OCset.M5 = ui->SV_QDS_56->value();
        OCset.M6 = ui->SV_QDS_57->value();
        OCset.M7 = ui->SV_QDS_58->value();

        OCset.U0 = ui->SV_QDS_61->value();
        OCset.U1 = ui->SV_QDS_62->value();
        OCset.U2 = ui->SV_QDS_63->value();
        OCset.U3 = ui->SV_QDS_64->value();
        OCset.U4 = ui->SV_QDS_65->value();
        OCset.U5 = ui->SV_QDS_66->value();

        OCset.F0 = ui->SV_QDS_68->currentText().remove(' ');
        OCset.F1 = ui->SV_QDS_69->currentText().remove(' ');
        OCset.F2 = ui->SV_QDS_70->currentText().remove(' ');
        //-----------------------load OCM_CONFIG----------------------------------------------------------------//
        if(!fs.Save_OCM_Config(pahtFM+"\\OCM_CONFIG.txt",OCset,spool,ms))
        {
            mm->setMessage("Update Parameter in OCM Config\n -Successful-",1);
        }
        else
        {
            mm->setMessage("Update Parameter in OCM Config\n -Fail-\nPlease check file OCM_CONFIG",1);
        }
        mm->exec();
    }
    okBtn_State(0);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_st_BackBtn_clicked()
{
    ui->SW->setCurrentIndex(1);
    Menu_State(1);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_me_UDBtn_clicked()
{
    if(m_menu)
    {
       Menu_State(0);
    }
    else
    {
       Menu_State(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_me_HomeBtn_clicked()
{
    this->Page_State(1);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_me_SettingBtn_clicked()
{
    this->Page_State(0);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_me_PlotBtn_clicked()
{
    if(m_process == 1)
    {
        this->Page_State(2);
    }
    else if(m_process == 2)
    {
        this->Page_State(5);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_me_SaveBtn_clicked()
{

}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_me_SentBtn_clicked()
{
    ui->me_SentBtn->setStyleSheet(bg_sent_on);
    ui->me_SentBtn->setEnabled(0);

    QString ms;
    GSentBox *sb = new GSentBox(this);
    sb->setWindowState(Qt::WindowActive);
    QStringList ln;
    if(m_process == 1)
    {
        ln << "emeraldout_elems.txt";
        ln << "emeraldout_events.txt";
        ln << "emeraldout_ocmlog.txt";
        ln << "emeraldout_ocmplan.txt";
        ln << "sat_pass.txt";
        sb->setSentBox("De-Orbit Simulation Module",this->pahtFM + "/MAN",ln,1,ms);
    }
    else if(m_process == 2)
    {
        ln << "emeraldout_elems.txt";
        ln << "emeraldout_events.txt";
        ln << "emeraldout_ocmlog.txt";
        ln << "emeraldout_ocmplan.txt";
        ln << "sat_pass.txt";
        sb->setSentBox("De-Orbit Simulation Module",this->pahtFM + "/MAN",ln,1,ms);
    }
    else
    {
        sb->setSentBox("De-Orbit Simulation Module",this->pahtFM,ln,1,ms);
    }

    if(sb->exec())
    {

    }
    ui->me_SentBtn->setStyleSheet(bg_sent_off);
    ui->me_SentBtn->setEnabled(1);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_me_ArchiveBtn_clicked()
{
    ui->me_SentBtn->setStyleSheet(bg_sent_on);
    ui->me_SentBtn->setEnabled(0);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_me_PrintBtn_clicked()
{

}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_in_StartBtn_clicked()
{
    QString ms;
    StartBtn_State(1);
    GMessage *mb = new GMessage(this);
    mb->setMessage("Are you certain that you want \nto start Computing De-Orbit?",0);

    if(mb->exec())
    {
        spool += "\n\n>> Start Computing De-Orbit MAN mode[" + fs.DateTime2Text() +"]";

        //-------------------------- Input file -----------------------------------------------------------//
        spool += "\n   Load Input file :";
        if(fs.Save_OV_Set(pahtFM+"\\OVSET.txt",OVSet,ui->m_in_StartSim_Dte->text(),spool,ms))
        {
            spool += "\n     ++Write Input file : OVSET --- [Not OK]";
            ms += "\nWrite Input file : OVSET --- [Not OK]\n";
        }

        OISet.Type = "DEO";
        OISet.Perigee_High = ui->m_in_PerigeeHigh_Dsb->value();
        OISet.Num_of_Split = ui->m_in_NumSpit_Dsb->value();
        OISet.Execut_Time = ui->m_in_StartEpoch_Dte->dateTime();
        OISet.Helium_Pressure = ui->m_ins_HP_Dsb->value();
        OISet.Helium_Temperature = ui->m_ins_HT_Dsb->value();
        OISet.Propellant_Temperature = ui->m_ins_PT_Dsb->value();
        OISet.Propellant_Mass = ui->m_ins_PM_Dsb->value();

        if(fs.Save_OCM_IND(pahtFM+"\\OCM_IN.txt",OISet,spool,ms))
        {
            spool += "\n     ++Write Input file : OCM_IN --- [Not OK]";
            ms += "\nWrite Input file : OCM_IN --- [Not OK]\n";
        }

        spool += "\n   Check Input file :";
        if(!fs.CheckInput("DOS",pahtFM,spool,ms))
        {
            //-------------------------- Process ------------------------------------------------------//
            spool += "\n\n   Start Processing...";
            QStringList m_arguments;
            double td = fs.GetRange_DateTime2jday(ui->m_in_StartSim_Dte,ui->m_in_EndSim_Dte);
            m_arguments << "-n" << "15" << "-S" << "-M" << "-G" << "-t" << QString::number(td,'f',2) << "-p" << ui->m_in_PrintStep_Dsb->text() << "-s" << "10.0" << "-m";
            if(m_Mode)m_arguments << "OTR";
            else m_arguments << "MAN";
            m_arguments << "OVSET.txt";

            GProcess *pp = new GProcess(this);
            QProcess *dos = new QProcess(this);
            connect(dos,SIGNAL(finished(int)),pp,SLOT(accept()));
            dos->setWorkingDirectory(pahtFM);
            dos->setProgram(pahtFM + "\\dos.exe");
            dos->setArguments(m_arguments);
            dos->start();

            if(pp->exec())
            {
                //-------------------------- Output --------------------------------------------------------------//
                QString thm = "";
                QStringList ls;
                thm += dos->readAllStandardOutput();
                ls = thm.split('\n');
                for(int i=0;i<ls.count();i++)
                {
                    spool += "\n   " + ls[i];
                }

                QFile file(pahtFM + "\\emeraldout_ocmlog.txt");
                if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    spool += "\n   ++Error Output : Orbit Maneouvre";
                }
                else
                {
                    QTextStream in(&file);
                    while(!in.atEnd())
                    {
                        spool += "\n   " + in.readLine();
                    }
                    file.close();
                }

                spool += "\n   De-Orbit Simulation : Result Computing OCM";
                spool += "\n   Save Output file : Result Prigee High in \"emeraldout_elems.txt\" --- [OK]";

                if(CreatePlot())
                {

                }
                else
                {
                    spool += "\n   Create Plot De-Orbit - (MAN Mode) --- [OK]";
                }
                if(CreateReport())
                {

                }
                else
                {
                    spool += "\n   Create Report De-Orbit - (MAN Mode) --- [OK]";
                }

                ui->m_outs_Overall_Dsb->setValue(fs.Perigee_High(ui->m_in_StartSim_Dte,ui->m_in_EndSim_Dte));
                ui->m_outs_Perigee_Dsb->setValue(ui->m_outs_Overall_Dsb->value()/ui->m_in_NumSpit_Dsb->value());
                ui->m_outs_Epoch_Dsb->setDateTime(ui->m_in_StartEpoch_Dte->dateTime());
                outToDir(pahtFM + "\\MAN");
                m_process = 1;
            }
        }
        spool += "\n>> End Computing De-Orbit MAN mode[" + fs.DateTime2Text() +"]";

        if(m_process == 1)
        {
            UpdateTemplate();
            this->Page_State(3);
            ui->me_PlotBtn->setEnabled(1);
        }
        ui->m_outT_SpoolPte->setPlainText(spool);
        ui->o_outT_SpoolPte->setPlainText(spool);
    }
    StartBtn_State(0);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_in_ChooseBtn_clicked()
{
    QFileDialog dg(this);
    dg.setAcceptMode(QFileDialog::AcceptOpen);
    dg.setFileMode(QFileDialog::AnyFile);
    dg.setDirectory("C:/FDS_Operation/Vectors/Orbit_vector");
    dg.setViewMode(QFileDialog::Detail);
    dg.setNameFilter("*.txt");
    dg.selectFile(ui->m_in_OVSet_COB->currentText()+".txt");
    if(dg.exec())
    {
        QFileInfo file(dg.selectedFiles().first());
        QFile::copy(file.absoluteFilePath(),"C:/FDS_Operation/Vectors/Orbit_vector/"+file.fileName());
        if(ui->m_in_OVSet_COB->findText(file.baseName()) == -1)
        {
            ui->m_in_OVSet_COB->addItem(file.baseName());
        }
        ui->m_in_OVSet_COB->setCurrentText(file.baseName());
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_out_TextBtn_clicked()
{
    this->Page_State(3);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_out_GraphBtn_clicked()
{
    this->Page_State(2);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_next_clicked()
{
    m_page++;
    if(m_page == 1)Page_State(1);
    else if(m_page == 2)Page_State(2);
    else if(m_page == 3)Page_State(4);
    else if(m_page >= 4)Page_State(5);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_back_clicked()
{
    m_page--;
    if(m_page <= 1)Page_State(1);
    else if(m_page == 2)Page_State(2);
    else if(m_page == 3)Page_State(4);
    else if(m_page == 4)Page_State(5);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_point1_clicked()
{
    Page_State(1);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_point2_clicked()
{
    Page_State(2);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_point3_clicked()
{
    Page_State(4);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_point4_clicked()
{
    Page_State(5);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_P_Btn_clicked()
{
    if(OCM_count < OCM_max)
    {
        OCM_count++;
        if(((OCM_count-1)/7) > ui->sup_input->currentIndex())
        {
            ui->sup_input->setCurrentIndex(OCM_count/7);
        }
        this->Input_State(0,OCM_count);
        Epoch_list[OCM_count]->setDateTime(Epoch_list[OCM_count-1]->dateTime());
        Delta_A_list[OCM_count]->setValue(Delta_A_list[OCM_count-1]->value());
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_D_Btn_clicked()
{
    if(OCM_count > 0)
    {
        this->Input_State(1,OCM_count);
        OCM_count--;
        if(((OCM_count-1)/7) != ui->sup_input->currentIndex())
        {
            ui->sup_input->setCurrentIndex((OCM_count-1)/7);
        }
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_Back_Btn_clicked()
{
    if(ui->sup_input->currentIndex() > 0)
    {
        ui->sup_input->setCurrentIndex(ui->sup_input->currentIndex()-1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_Next_Btn_clicked()
{
    if(OCM_count > ((ui->sup_input->currentIndex()+1)*7))
    {
        if(ui->sup_input->currentIndex() < (ui->sup_input->count()-1))
        {
            ui->sup_input->setCurrentIndex(ui->sup_input->currentIndex()+1);
        }
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_Start_Btn_clicked()
{
    QString ms;
    int k = 0;
    RunBtn_State(1);
    GMessage *mb = new GMessage(this);
    mb->setMessage("Are you certain that you want \nto start Computing De-Orbit?",0);

    if(mb->exec())
    {
        if(!Check_InputPlan())
        {
            spool += "\n\n>> Start Computing De-Orbit OTR mode[" + fs.DateTime2Text() +"]";

            //-------------------------- Input file -----------------------------------------------------------//
            spool += "\n   Load Input file :";
            QDateTimeEdit st;
            st.setDateTime(Epoch_list[1]->dateTime());
            st.setDate(st.date().addDays(-2));
            if(fs.Save_OV_Set(pahtFM+"\\OVSET.txt",OVSet,st.dateTime().toString("yyyy/MM/dd hh:mm:sss.zzz"),spool,ms))
            {
                spool += "\n     ++Write Input file : OVSET --- [Not OK]";
                ms += "\nWrite Input file : OVSET --- [Not OK]\n";
            }

            OISet.Type = "DEO";
            OISet.Perigee_High = ui->m_in_PerigeeHigh_Dsb->value();
            OISet.Num_of_Split = ui->m_in_NumSpit_Dsb->value();
            OISet.Execut_Time = ui->m_in_StartEpoch_Dte->dateTime();
            OISet.Helium_Pressure = ui->m_ins_HP_Dsb->value();
            OISet.Helium_Temperature = ui->m_ins_HT_Dsb->value();
            OISet.Propellant_Temperature = ui->m_ins_PT_Dsb->value();
            OISet.Propellant_Mass = ui->m_ins_PM_Dsb->value();

            if(fs.Save_OCM_IND(pahtFM+"\\OCM_IN.txt",OISet,spool,ms))
            {
                spool += "\n     ++Write Input file : OCM_IN --- [Not OK]";
                ms += "\nWrite Input file : OCM_IN --- [Not OK]\n";
            }

            QFile file(pahtFM + "\\ORBTRAN_IN.txt");
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                spool += "\n     ++Can not open file : Add input file ORBTRAN_IN";
                GMessage *wn = new GMessage(this);
                wn->setMessage("Can not open file : ORBTRAN_IN\nPlease check file ORBTRAN_IN",1);
                wn->exec();
            }
            else
            {
                QTextStream out(&file);
                out << "#####################################################################################################################################";
                out << "\n#\n#Input file for Orbit transfer manoeuvre plan\n#";
                out << "\n#####################################################################################################################################";

                QString ss = "";
                for(int i=1;i<=OCM_count;i++)
                {
                    k = k + Num_of_Im_list[i]->value();

                    ss += "\nOCM" + Num_of_OCM_list[i]->text();
                    ss += ": Type: " + TypeOCM_list[i]->currentText().section(' ',-1);
                    ss += " Number_Of_Impulse: " + QString::number(Num_of_Im_list[i]->value());
                    ss += " Earliest_Epoch: " + Epoch_list[i]->text();
                    ss += " Delta-rp(km): " + QString::number(Delta_A_list[i]->value(),'f',4);
                    ss += " Delta-i(deg):  0.0000";
                }
                out << "\nNumber_of_Manoeuvre: " + QString::number(k);
                out << ss;
                file.close();
                spool += "\n     ++Write Input file : ORBTRAN_IN --- [OK]";
            }
            spool += "\n   Check Input file :";
            if(!fs.CheckInput("DOS",pahtFM,spool,ms))
            {
                //-------------------------- Process ------------------------------------------------------//
                spool += "\n\n   Start Processing...";
                QStringList m_arguments;
                double td = fs.GetRange_DateTime2jday(Epoch_list[1],Epoch_list[OCM_count]);
                m_arguments << "-n" << "15" << "-S" << "-M" << "-G" << "-t" << QString::number(td+4,'f',2) << "-p" << ui->m_in_PrintStep_Dsb->text() << "-s" << "10.0" << "-m" << "OTR" << "OVSET.txt";

                GProcess *pp = new GProcess(this);
                QProcess *dos = new QProcess(this);
                connect(dos,SIGNAL(finished(int)),pp,SLOT(accept()));
                dos->setWorkingDirectory(pahtFM);
                dos->setProgram(pahtFM + "\\dos.exe");
                dos->setArguments(m_arguments);
                dos->start();

                if(pp->exec())
                {
                    //-------------------------- Output --------------------------------------------------------------//
                    QString thm = "";
                    QStringList ls;
                    thm += dos->readAllStandardOutput();
                    ls = thm.split('\n');
                    for(int i=0;i<ls.count();i++)
                    {
                        spool += "\n   " + ls[i];
                    }

                    QFile file(pahtFM + "\\emeraldout_ocmlog.txt");
                    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        spool += "\n   ++Error Output : Orbit Maneouvre";
                    }
                    else
                    {
                        QTextStream in(&file);
                        while(!in.atEnd())
                        {
                            spool += "\n   " + in.readLine();
                        }
                        file.close();
                    }

                    spool += "\n   De-Orbit Simulation : Result Computing OCM";
                    spool += "\n   Save Output file : Result Prigee High in \"emeraldout_elems.txt\" --- [OK]";

                    if(CreatePlot())
                    {

                    }
                    else
                    {
                        spool += "\n   Create Plot De-Orbit - (OTR Mode) --- [OK]";
                    }
                    if(CreateReport())
                    {
                        GMessage *er = new GMessage(this);
                        er->setMessage("Error Output file\nPlease check file ocmplan and sat_pass",1);
                        er->exec();
                        return;
                    }
                    else
                    {
                        spool += "\n   Create Report De-Orbit - (OTR Mode) --- [OK]";
                    }
                    ui->o_outs_Overall_Dsb->setValue(fs.Perigee_High(ui->m_in_StartSim_Dte,ui->m_in_EndSim_Dte));
                    ui->o_outs_NumMAN_Dsb->setValue(k);
                    outToDir(pahtFM + "\\OTR");
                    m_process = 2;
                }
            }
            spool += "\n>> End Computing De-Orbit OTR mode[" + fs.DateTime2Text() +"]";

            if(m_process == 2)
            {
                UpdateTemplate();
                this->Page_State(5);
            }
            ui->m_outT_SpoolPte->setPlainText(spool);
            ui->o_outT_SpoolPte->setPlainText(spool);
        }
        else
        {
            GMessage *er = new GMessage(this);
            er->setMessage("!Check Planning Input not pass\nPlease check page Planning Input",1);
            er->exec();
        }
    }
    RunBtn_State(0);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outG_SG1_Btn_clicked()
{
    this->GSGBtn_State(1);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outG_SG2_Btn_clicked()
{
    this->GSGBtn_State(2);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outG_SG3_Btn_clicked()
{
    this->GSGBtn_State(3);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outG_SG4_Btn_clicked()
{
    this->GSGBtn_State(4);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outG_SG5_Btn_clicked()
{
    this->GSGBtn_State(5);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outT_SG1_Btn_clicked()
{
    this->TSGBtn_State(1);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outT_SG2_Btn_clicked()
{
    this->TSGBtn_State(2);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outT_SG3_Btn_clicked()
{
    this->TSGBtn_State(3);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outT_GraphBtn_clicked()
{
    ui->sub_Main->setCurrentIndex(3);
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_o_outG_TextBtn_clicked()
{
    ui->sub_Main->setCurrentIndex(4);
}
//----------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------//
//-------------------------------------> State Function <---------------------------------------------------//
//----------------------------------------------------------------------------------------------------------//
void DOS::on_sup_setting_currentChanged(int arg1)
{
    if((arg1>=0) && (arg1<=3))
    {
        SGP1_State(1);
        SGP2_State(0);
        SGP3_State(0);
        SGP4_State(0);
    }
    else if(arg1==4)
    {
        SGP1_State(0);
        SGP2_State(1);
        SGP3_State(0);
        SGP4_State(0);
    }
    else if(arg1==5)
    {
        SGP1_State(0);
        SGP2_State(0);
        SGP3_State(1);
        SGP4_State(0);
    }
    else if(arg1==6)
    {
        SGP1_State(0);
        SGP2_State(0);
        SGP3_State(0);
        SGP4_State(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::okBtn_State(bool state)
{
    if(state)
    {
        ui->setOKBtn->setStyleSheet(bg_ok_on);
        ui->setOKBtn->setEnabled(0);
    }
    else
    {
        ui->setOKBtn->setStyleSheet(bg_ok_off);
        ui->setOKBtn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::StartBtn_State(bool state)
{
    if(state)
    {
        ui->m_in_StartBtn->setStyleSheet(bg_Start_on);
        ui->m_in_StartBtn->setEnabled(0);
    }
    else
    {
        ui->m_in_StartBtn->setStyleSheet(bg_Start_off);
        ui->m_in_StartBtn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::RunBtn_State(bool state)
{
    if(state)
    {
        ui->Start_Btn->setStyleSheet(bg_Run_on);
        ui->Start_Btn->setEnabled(0);
    }
    else
    {
        ui->Start_Btn->setStyleSheet(bg_Run_off);
        ui->Start_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Save_State(bool state)
{
    if(state)
    {
        ui->me_SaveBtn->setStyleSheet(bg_save_on);
        ui->me_SaveBtn->setEnabled(0);
    }
    else
    {
        ui->me_SaveBtn->setStyleSheet(bg_save_off);
        ui->me_SaveBtn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Sent_State(bool state)
{
    if(state)
    {
        ui->me_SentBtn->setStyleSheet(bg_sent_on);
        ui->me_SentBtn->setEnabled(0);
    }
    else
    {
        ui->me_SentBtn->setStyleSheet(bg_sent_off);
        ui->me_SentBtn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Print_State(bool state)
{
    if(state)
    {
        ui->me_PrintBtn->setStyleSheet(bg_print_on);
        ui->me_PrintBtn->setEnabled(0);
    }
    else
    {
        ui->me_PrintBtn->setStyleSheet(bg_print_off);
        ui->me_PrintBtn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Archive_State(bool state)
{
    if(state)
    {
        ui->me_ArchiveBtn->setStyleSheet(bg_archive_on);
        ui->me_ArchiveBtn->setEnabled(0);
    }
    else
    {
        ui->me_ArchiveBtn->setStyleSheet(bg_archive_off);
        ui->me_ArchiveBtn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::SGP1_State(bool state)
{
    if(state)
    {
        ui->setPgBtn_1->setStyleSheet(bg_setMode_on);
        ui->setPgBtn_1->setEnabled(0);
    }
    else
    {
        ui->setPgBtn_1->setStyleSheet(bg_setMode_off);
        ui->setPgBtn_1->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::SGP2_State(bool state)
{
    if(state)
    {
        ui->setPgBtn_2->setStyleSheet(bg_setMode_on);
        ui->setPgBtn_2->setEnabled(0);
    }
    else
    {
        ui->setPgBtn_2->setStyleSheet(bg_setMode_off);
        ui->setPgBtn_2->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::SGP3_State(bool state)
{
    if(state)
    {
        ui->setPgBtn_3->setStyleSheet(bg_setMode_on);
        ui->setPgBtn_3->setEnabled(0);
    }
    else
    {
        ui->setPgBtn_3->setStyleSheet(bg_setMode_off);
        ui->setPgBtn_3->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::SGP4_State(bool state)
{
    if(state)
    {
        ui->setPgBtn_4->setStyleSheet(bg_setMode_on);
        ui->setPgBtn_4->setEnabled(0);
    }
    else
    {
        ui->setPgBtn_4->setStyleSheet(bg_setMode_off);
        ui->setPgBtn_4->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Menu_State(bool state)
{
    if(state)
    {
        ui->Menu->move(ui->Menu->x(),0);
        ui->me_UDBtn->setIcon(Icon_Up);
        m_menu = 1;
    }
    else
    {
        ui->Menu->move(ui->Menu->x(),-1080*sy);
        ui->me_UDBtn->setIcon(Icon_Down);
        m_menu = 0;
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::TG_State(bool state)
{
    if(state)
    {
        ui->m_out_H1_Lb->setText("Text");
        ui->m_out_GraphBtn->setStyleSheet(bg_Graph_off);
        ui->m_out_GraphBtn->setEnabled(1);
        ui->m_out_TextBtn->setStyleSheet(bg_Text_on);
        ui->m_out_TextBtn->setEnabled(0);
    }
    else
    {
        ui->m_out_H1_Lb->setText("Graph");
        ui->m_out_GraphBtn->setStyleSheet(bg_Graph_on);
        ui->m_out_GraphBtn->setEnabled(0);
        ui->m_out_TextBtn->setStyleSheet(bg_Text_off);
        ui->m_out_TextBtn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Point_State(int page)
{
    if(page == 1)
    {
        ui->m_point1->setStyleSheet(bg_point_on);
        ui->m_point1->setEnabled(0);
        ui->m_point2->setStyleSheet(bg_point_off);
        ui->m_point2->setEnabled(1);
        ui->m_point3->setStyleSheet(bg_point_off);
        ui->m_point3->setEnabled(1);
        ui->m_point4->setStyleSheet(bg_point_off);
        ui->m_point4->setEnabled(1);
        m_page = 1;
    }
    else if(page == 2)
    {
        ui->m_point1->setStyleSheet(bg_point_off);
        ui->m_point1->setEnabled(1);
        ui->m_point2->setStyleSheet(bg_point_on);
        ui->m_point2->setEnabled(0);
        ui->m_point3->setStyleSheet(bg_point_off);
        ui->m_point3->setEnabled(1);
        ui->m_point4->setStyleSheet(bg_point_off);
        ui->m_point4->setEnabled(1);
        m_page = 2;
    }
    else if(page == 3)
    {
        ui->m_point1->setStyleSheet(bg_point_off);
        ui->m_point1->setEnabled(1);
        ui->m_point2->setStyleSheet(bg_point_off);
        ui->m_point2->setEnabled(1);
        ui->m_point3->setStyleSheet(bg_point_on);
        ui->m_point3->setEnabled(0);
        ui->m_point4->setStyleSheet(bg_point_off);
        ui->m_point4->setEnabled(1);
        m_page = 3;
    }
    else if(page == 4)
    {
        ui->m_point1->setStyleSheet(bg_point_off);
        ui->m_point1->setEnabled(1);
        ui->m_point2->setStyleSheet(bg_point_off);
        ui->m_point2->setEnabled(1);
        ui->m_point3->setStyleSheet(bg_point_off);
        ui->m_point3->setEnabled(1);
        ui->m_point4->setStyleSheet(bg_point_on);
        ui->m_point4->setEnabled(0);
        m_page = 4;
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Page_State(int page)
{
    if(page == 0) // Page Setting
    {
        ui->SW->setCurrentIndex(0);
        this->Menu_State(0);
    }
    else if(page == 1) // Page Input Mode M
    {
        ui->SW->setCurrentIndex(1);
        ui->sub_Main->setCurrentIndex(0);
        ui->sub_Main2->setCurrentIndex(0);
        Point_State(1);
    }
    else if(page == 2) // Page Output Graph Mode M
    {
        ui->SW->setCurrentIndex(1);
        ui->sub_Main->setCurrentIndex(1);
        ui->sub_Main2->setCurrentIndex(1);
        ui->page_OutputMAN_TG->setCurrentIndex(0);
        TG_State(0);
        Point_State(2);
    }
    else if(page == 3) // Page Output Text Mode M
    {
        ui->SW->setCurrentIndex(1);
        ui->sub_Main->setCurrentIndex(1);
        ui->sub_Main2->setCurrentIndex(1);
        ui->page_OutputMAN_TG->setCurrentIndex(1);
        TG_State(1);
        Point_State(2);
    }
    else if(page == 4) // Page Input Mode OTR
    {
        ui->SW->setCurrentIndex(1);
        ui->sub_Main->setCurrentIndex(2);
        ui->sub_Main2->setCurrentIndex(1);
        Point_State(3);
    }
    else if(page == 5) // Page Output Graph Mode OTR
    {
        ui->SW->setCurrentIndex(1);
        ui->sub_Main->setCurrentIndex(3);
        ui->sub_Main2->setCurrentIndex(2);
        Point_State(4);
    }
    else if(page == 6) // Page Output Text Mode OTR
    {
        ui->SW->setCurrentIndex(1);
        ui->sub_Main->setCurrentIndex(4);
        ui->sub_Main2->setCurrentIndex(2);
        Point_State(4);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::Input_State(bool on_off, int state)
{
    if((state > 0) && (state <= OCM_max))
    {
        Num_of_OCM_list[state]->setHidden(on_off);
        TypeOCM_list[state]->setHidden(on_off);
        Num_of_Im_list[state]->setHidden(on_off);
        Epoch_list[state]->setHidden(on_off);
        Delta_A_list[state]->setHidden(on_off);
    }
    else
    {
        for(int i=1;i<=OCM_max;i++)
        {
            Num_of_OCM_list[i]->setHidden(on_off);
            TypeOCM_list[i]->setHidden(on_off);
            Num_of_Im_list[i]->setHidden(on_off);
            Epoch_list[i]->setHidden(on_off);
            Delta_A_list[i]->setHidden(on_off);
        }
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::GSG1Btn_State(bool state)
{
    if(state)
    {
        ui->o_outG_SG1_Btn->setStyleSheet(bg_GSGBtn_on);
        ui->o_outG_SG1_Btn->setEnabled(0);
    }
    else
    {
        ui->o_outG_SG1_Btn->setStyleSheet(bg_GSGBtn_off);
        ui->o_outG_SG1_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::GSG2Btn_State(bool state)
{
    if(state)
    {
        ui->o_outG_SG2_Btn->setStyleSheet(bg_GSGBtn_on);
        ui->o_outG_SG2_Btn->setEnabled(0);
    }
    else
    {
        ui->o_outG_SG2_Btn->setStyleSheet(bg_GSGBtn_off);
        ui->o_outG_SG2_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::GSG3Btn_State(bool state)
{
    if(state)
    {
        ui->o_outG_SG3_Btn->setStyleSheet(bg_GSGBtn_on);
        ui->o_outG_SG3_Btn->setEnabled(0);
    }
    else
    {
        ui->o_outG_SG3_Btn->setStyleSheet(bg_GSGBtn_off);
        ui->o_outG_SG3_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::GSG4Btn_State(bool state)
{
    if(state)
    {
        ui->o_outG_SG4_Btn->setStyleSheet(bg_GSGBtn_on);
        ui->o_outG_SG4_Btn->setEnabled(0);
    }
    else
    {
        ui->o_outG_SG4_Btn->setStyleSheet(bg_GSGBtn_off);
        ui->o_outG_SG4_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::GSG5Btn_State(bool state)
{
    if(state)
    {
        ui->o_outG_SG5_Btn->setStyleSheet(bg_GSGBtn_on);
        ui->o_outG_SG5_Btn->setEnabled(0);
    }
    else
    {
        ui->o_outG_SG5_Btn->setStyleSheet(bg_GSGBtn_off);
        ui->o_outG_SG5_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::GSGBtn_State(int sp)
{
    if(sp == 1)
    {
        GSG1Btn_State(1);
        GSG2Btn_State(0);
        GSG3Btn_State(0);
        GSG4Btn_State(0);
        GSG5Btn_State(0);
        ui->sub_OutG_OTR->setCurrentIndex(0);
    }
    else if(sp == 2)
    {
        GSG1Btn_State(0);
        GSG2Btn_State(1);
        GSG3Btn_State(0);
        GSG4Btn_State(0);
        GSG5Btn_State(0);
        ui->sub_OutG_OTR->setCurrentIndex(1);
    }
    else if(sp == 3)
    {
        GSG1Btn_State(0);
        GSG2Btn_State(0);
        GSG3Btn_State(1);
        GSG4Btn_State(0);
        GSG5Btn_State(0);
        ui->sub_OutG_OTR->setCurrentIndex(2);
    }
    else if(sp == 4)
    {
        GSG1Btn_State(0);
        GSG2Btn_State(0);
        GSG3Btn_State(0);
        GSG4Btn_State(1);
        GSG5Btn_State(0);
        ui->sub_OutG_OTR->setCurrentIndex(3);
    }
    else if(sp == 5)
    {
        GSG1Btn_State(0);
        GSG2Btn_State(0);
        GSG3Btn_State(0);
        GSG4Btn_State(0);
        GSG5Btn_State(1);
        ui->sub_OutG_OTR->setCurrentIndex(4);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::TSG1Btn_State(bool state)
{
    if(state)
    {
        ui->o_outT_SG1_Btn->setStyleSheet(bg_TSGBtn_on);
        ui->o_outT_SG1_Btn->setEnabled(0);
    }
    else
    {
        ui->o_outT_SG1_Btn->setStyleSheet(bg_TSGBtn_off);
        ui->o_outT_SG1_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::TSG2Btn_State(bool state)
{
    if(state)
    {
        ui->o_outT_SG2_Btn->setStyleSheet(bg_TSGBtn_on);
        ui->o_outT_SG2_Btn->setEnabled(0);
    }
    else
    {
        ui->o_outT_SG2_Btn->setStyleSheet(bg_TSGBtn_off);
        ui->o_outT_SG2_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::TSG3Btn_State(bool state)
{
    if(state)
    {
        ui->o_outT_SG3_Btn->setStyleSheet(bg_TSGBtn_on);
        ui->o_outT_SG3_Btn->setEnabled(0);
    }
    else
    {
        ui->o_outT_SG3_Btn->setStyleSheet(bg_TSGBtn_off);
        ui->o_outT_SG3_Btn->setEnabled(1);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::TSGBtn_State(int sp)
{
    if(sp == 1)
    {
        TSG1Btn_State(1);
        TSG2Btn_State(0);
        TSG3Btn_State(0);
        ui->sub_OutT_OTR->setCurrentIndex(0);
    }
    else if(sp == 2)
    {
        TSG1Btn_State(0);
        TSG2Btn_State(1);
        TSG3Btn_State(0);
        ui->sub_OutT_OTR->setCurrentIndex(1);
    }
    else if(sp == 3)
    {
        TSG1Btn_State(0);
        TSG2Btn_State(0);
        TSG3Btn_State(1);
        ui->sub_OutT_OTR->setCurrentIndex(2);
    }
}
//----------------------------------------------------------------------------------------------------------//
void DOS::on_m_outT_SearchBtn_clicked()
{
    input = "";
    start = 0;
    stop = 0;
    input = ui->m_outT_IndexS_Led->text();
    ui->m_outT_SpoolPte->setPlainText(ui->m_outT_SpoolPte->toPlainText());
    spool_s = (ui->m_outT_SpoolPte->toPlainText().toLower()).split(input.toLower());
    stop = input.length();
    //QTextCursor cursor(ui->txtShow_Search->toPlainText());
    QTextCharFormat fmt;
    fmt.setBackground(Qt::darkBlue);
    QTextCursor cursor = ui->m_outT_SpoolPte->textCursor();
    QScrollBar *sb = ui->m_outT_SpoolPte->verticalScrollBar();

    if(input!=check)
    {
        startL.clear();
        stopL.clear();
        num = 0;
    }
    if(num<spool_s.length()-1)
    {
        for(int i=0;i<spool_s.length()-1;i++)
        {
            if(spool_s[i].trimmed()!="")
            {
                start += spool_s[i].length();
                startL.append(start);
                stopL.append(start+stop);
                start = start + stop;
                bunL.append(i);
            }
        }
        if(num<=startL.length() && num<=stopL.length())
        {
            cursor.movePosition(QTextCursor::End);
            cursor.setPosition(startL[num], QTextCursor::MoveAnchor);
            cursor.setPosition(stopL[num], QTextCursor::KeepAnchor);
            cursor.setCharFormat(fmt);
            sb->setValue((bunL[num]*100)/50);
            num++;
            check = input;
        }
    }
    else
    {
        num = 0;
    }
}
//----------------------------------------------------------------------------------------------------------//
