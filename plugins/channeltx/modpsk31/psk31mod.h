///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017-2022 Edouard Griffiths, F4EXB <f4exb06@gmail.com>          //
// Copyright (C) 2020-2021, 2023 Jon Beniston, M7RCE <jon@beniston.com>          //
// Copyright (C) 2020 Kacper Michajłow <kasper93@gmail.com>                      //
// Copyright (C) 2022 Jiří Pinkava <jiri.pinkava@rossum.ai>                      //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
// (at your option) any later version.                                           //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef PLUGINS_CHANNELTX_MODPSK31_PSK31MOD_H_
#define PLUGINS_CHANNELTX_MODPSK31_PSK31MOD_H_

#include <vector>
#include <iostream>
#include <fstream>

#include <QRecursiveMutex>
#include <QNetworkRequest>

#include "dsp/basebandsamplesource.h"
#include "dsp/spectrumvis.h"
#include "channel/channelapi.h"
#include "util/message.h"

#include "psk31modsettings.h"

class QNetworkAccessManager;
class QNetworkReply;
class QThread;
class QUdpSocket;
class DeviceAPI;
class PSK31Baseband;
class ObjectPipe;

class PSK31 : public BasebandSampleSource, public ChannelAPI {
public:
    class MsgConfigurePSK31 : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        const PSK31Settings& getSettings() const { return m_settings; }
        bool getForce() const { return m_force; }

        static MsgConfigurePSK31* create(const PSK31Settings& settings, bool force)
        {
            return new MsgConfigurePSK31(settings, force);
        }

    private:
        PSK31Settings m_settings;
        bool m_force;

        MsgConfigurePSK31(const PSK31Settings& settings, bool force) :
            Message(),
            m_settings(settings),
            m_force(force)
        { }
    };

    class MsgTx : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        static MsgTx* create() {
            return new MsgTx();
        }

   private:
        MsgTx() :
            Message()
        { }
    };

    class MsgReportTx : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        const QString& getText() const { return m_text; }
        int getBufferedCharacters() const { return m_bufferedCharacters; }

        static MsgReportTx* create(const QString& text, int bufferedCharacters) {
            return new MsgReportTx(text, bufferedCharacters);
        }

   private:
       QString m_text;
       int m_bufferedCharacters;

       MsgReportTx(const QString& text, int bufferedCharacters) :
           Message(),
           m_text(text),
           m_bufferedCharacters(bufferedCharacters)
        { }
    };

    class MsgTXText : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        static MsgTXText* create(QString text)
        {
            return new MsgTXText(text);
        }

        QString m_text;

   private:

       MsgTXText(QString text) :
            Message(),
            m_text(text)
        { }
    };

    //=================================================================

    PSK31(DeviceAPI *deviceAPI);
    virtual ~PSK31();
    virtual void destroy() { delete this; }
    virtual void setDeviceAPI(DeviceAPI *deviceAPI);
    virtual DeviceAPI *getDeviceAPI() { return m_deviceAPI; }

    virtual void start();
    virtual void stop();
    virtual void pull(SampleVector::iterator& begin, unsigned int nbSamples);
    virtual void pushMessage(Message *msg) { m_inputMessageQueue.push(msg); }
    virtual QString getSourceName() { return objectName(); }

    virtual void getIdentifier(QString& id) { id = objectName(); }
    virtual QString getIdentifier() const { return objectName(); }
    virtual void getTitle(QString& title) { title = m_settings.m_title; }
    virtual qint64 getCenterFrequency() const { return m_settings.m_inputFrequencyOffset; }
    virtual void setCenterFrequency(qint64 frequency);

    virtual QByteArray serialize() const;
    virtual bool deserialize(const QByteArray& data);

    virtual int getNbSinkStreams() const { return 1; }
    virtual int getNbSourceStreams() const { return 0; }

    virtual qint64 getStreamCenterFrequency(int streamIndex, bool sinkElseSource) const
    {
        (void) streamIndex;
        (void) sinkElseSource;
        return m_settings.m_inputFrequencyOffset;
    }

    virtual int webapiSettingsGet(
                SWGSDRangel::SWGChannelSettings& response,
                QString& errorMessage);

    virtual int webapiWorkspaceGet(
            SWGSDRangel::SWGWorkspaceInfo& response,
            QString& errorMessage);

    virtual int webapiSettingsPutPatch(
                bool force,
                const QStringList& channelSettingsKeys,
                SWGSDRangel::SWGChannelSettings& response,
                QString& errorMessage);

    virtual int webapiReportGet(
                SWGSDRangel::SWGChannelReport& response,
                QString& errorMessage);

    virtual int webapiActionsPost(
            const QStringList& channelActionsKeys,
            SWGSDRangel::SWGChannelActions& query,
            QString& errorMessage);

    static void webapiFormatChannelSettings(
        SWGSDRangel::SWGChannelSettings& response,
        const PSK31Settings& settings);

    static void webapiUpdateChannelSettings(
            PSK31Settings& settings,
            const QStringList& channelSettingsKeys,
            SWGSDRangel::SWGChannelSettings& response);

    SpectrumVis *getSpectrumVis() { return &m_spectrumVis; }
    double getMagSq() const;
    void setLevelMeter(QObject *levelMeter);
    uint32_t getNumberOfDeviceStreams() const;
    int getSourceChannelSampleRate() const;
    void setMessageQueueToGUI(MessageQueue* queue) override;

    static const char* const m_channelIdURI;
    static const char* const m_channelId;

private:
    enum RateState {
        RSInitialFill,
        RSRunning
    };

    DeviceAPI* m_deviceAPI;
    QThread *m_thread;
    PSK31Baseband* m_basebandSource;
    PSK31Settings m_settings;
    SpectrumVis m_spectrumVis;

    SampleVector m_sampleBuffer;
    QRecursiveMutex m_settingsMutex;

    int m_sampleRate;

    QNetworkAccessManager *m_networkManager;
    QNetworkRequest m_networkRequest;
    QUdpSocket *m_udpSocket;

    virtual bool handleMessage(const Message& cmd);
    void applySettings(const PSK31Settings& settings, bool force = false);
    void sendSampleRateToDemodAnalyzer();
    void webapiFormatChannelReport(SWGSDRangel::SWGChannelReport& response);
    void webapiReverseSendSettings(QList<QString>& channelSettingsKeys, const PSK31Settings& settings, bool force);
    void sendChannelSettings(
        const QList<ObjectPipe*>& pipes,
        QList<QString>& channelSettingsKeys,
        const PSK31Settings& settings,
        bool force
    );
    void webapiFormatChannelSettings(
        QList<QString>& channelSettingsKeys,
        SWGSDRangel::SWGChannelSettings *swgChannelSettings,
        const PSK31Settings& settings,
        bool force
    );
    void openUDP(const PSK31Settings& settings);
    void closeUDP();

private slots:
    void networkManagerFinished(QNetworkReply *reply);
    void udpRx();
};


#endif /* PLUGINS_CHANNELTX_MODPSK31_PSK31MOD_H_ */
