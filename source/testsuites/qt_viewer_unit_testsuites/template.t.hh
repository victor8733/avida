#ifndef TEMPLATE_T_HH
#define TEMPLATE_T_HH

#ifndef QT_TEST_CASE_HH
#include "qt_test_case.hh"
#endif

#ifndef TEST_CASE_H
#include "third-party/yaktest/test_case.h"
#endif
#ifndef TEXT_TEST_INTERPRETER_H
#include "third-party/yaktest/text_test_interpreter.h"
#endif
#ifndef TEST_RESULT_H
#include "third-party/yaktest/test_result.h"
#endif

#ifndef QLAYOUT_H
#include <qlayout.h>
#endif
#ifndef QPUSHBUTTON_H
#include <qpushbutton.h>
#endif
#ifndef QWIDGET_H
#include <qwidget.h>
#endif

#include <iostream>

class myWidget : public QWidget {
Q_OBJECT
public:
  QPushButton *m_pb;
  explicit myWidget(QWidget *parent = 0, const char *name = 0, WFlags f = 0)
  : QWidget(parent, name, f), m_pb(0)
  {
    QVBoxLayout *layout = new QVBoxLayout(this, 10, -1, "<myWidget(layout)>");
    m_pb = new QPushButton("foo", this, "<myWidget::m_pb>");
    layout->addWidget(m_pb);
    connect(m_pb, SIGNAL(clicked()), this, SIGNAL(clicked()));
  }
signals:
  void clicked();
};

class cTemplateTest : public cQtTestCase {
Q_OBJECT
protected:
  myWidget *m_w;
public:
  cTemplateTest(int argc, char **argv) : cQtTestCase(argc, argv) { }
public slots:
  void buttonClicked(){
    resetDeadMan();
    std::cout << "buttonClicked..." << std::endl;
    test_is_true(true);
    restartTimer();
  }
public:
  virtual void test() {
    m_w = new myWidget(0, "<cTemplateTest::(myWidget *)m_w>", 0);
    m_w->show(); m_w->raise();
    connect(m_w, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    tFunctor twiddle_functor(this, &cQtTestCase::twiddle);
    tFunctor click_functor(m_w->m_pb, &QPushButton::animateClick);

    pushFunctor(twiddle_functor);
    pushFunctor(twiddle_functor);
    pushFunctor(click_functor);

    execApp();

    if(m_w){ delete m_w; m_w = 0; }
  }
};

namespace nDemoTestsuite {
  class cTestSuite : public test_case {
  public: cTestSuite(int argc, char **argv) : test_case() {
    adopt_test_case(new cTemplateTest(argc, argv)); 
  } };
}

#endif
