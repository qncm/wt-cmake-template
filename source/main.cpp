#include <Wt/WAnchor>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WLink>
#include <Wt/WText>
#include <Wt/WString>

using Wt::WText;
using Wt::WContainerWidget;

inline Wt::WString tr(const char * key) {
    return Wt::WString::tr(key);
}

class ControlExample: public Wt::WApplication {
private:
    WContainerWidget* _content;
    Wt::WString appName;

public:
    ControlExample(const Wt::WEnvironment &env): Wt::WApplication(env),
        _content{nullptr},
        appName {tr("application-name")}
    {
        internalPathChanged().connect(this
                              , &ControlExample::onInternalPathChange);
        header();
        home();
        sidebar();
        footer();

        styleSheet().addRule("#header", "background-color: #262626; color: #fff; padding: 0.1em 0.5em;");
        styleSheet().addRule("#content", "display: inline-block; width: 65%; padding: 0.5em;");
        styleSheet().addRule("#sidebar", "display: inline-block; width: 30%; padding: 0.5em;");
        styleSheet().addRule("#footer", "background-color: #262626; color: #fff; padding: 0.5em;");
        styleSheet().addRule("BODY", "background-color: #F0F8FF;");

    }

    WContainerWidget* content() {
        if (_content == nullptr) {
            _content = new WContainerWidget{root()};
            _content->setId("content");
        }
        return _content;
    }

    void onInternalPathChange() {
        assert(_content != nullptr);
        content()->clear();
        if (internalPath() == "/") {
            home();
        }
        else if (internalPath() == "/page1") {
            page1();
        }
    }

    void header() {
        auto header = new WContainerWidget{root()};
        header->setId("header");
        header->addWidget(new WText{tr("application-name")});

    }

    void sidebar() {
        auto sidebar = new WContainerWidget{root()};
        sidebar->setId("sidebar");
        sidebar->addWidget(new WText(tr("sidebar-content")));
    }

    void footer() {
        auto footer = new WContainerWidget{root()};
        footer->setId("footer");
        footer->addWidget(new WText(tr("development-note")));
    }

    void home() {
        auto *t = new WText{tr("home-page-content")};
        t->setInternalPathEncoding(true);
        content()->addWidget(t);

    }

    void page1() {
        content()->addWidget(new WText{tr("page1-content")});
        new Wt::WAnchor{Wt::WLink{Wt::WLink::InternalPath, "/"},
	                        tr("home-link-text"), content()};
    }

};

Wt::WApplication* createApplication(const Wt::WEnvironment &env) {
    auto app = new ControlExample(env);
    app->setLocale(Wt::WLocale{"en"});
    app->messageResourceBundle().use("strings");
    app->setTitle(tr("application-name"));
    return app;
}

int main(int argc, char** argv) {
    return WRun(argc, argv, &createApplication);
}
