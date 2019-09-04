///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 Edouard Griffiths, F4EXB                                   //
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

#ifndef SDRBASE_DEVICE_DEVICEAPI_H_
#define SDRBASE_DEVICE_DEVICEAPI_H_

#include <QObject>
#include <QString>
#include <QTimer>

#include "export.h"

class BasebandSampleSink;
class ThreadedBasebandSampleSink;
class ThreadedBasebandSampleSource;
class MIMOChannel;
class ChannelAPI;
class DeviceSampleSink;
class DeviceSampleSource;
class DeviceSampleMIMO;
class MessageQueue;
class PluginInterface;
class PluginInstanceGUI;
class DSPDeviceSourceEngine;
class DSPDeviceSinkEngine;
class DSPDeviceMIMOEngine;
class Preset;

class SDRBASE_API DeviceAPI : public QObject {
    Q_OBJECT
public:
    enum StreamType //!< This is the same enum as in PluginInterface
    {
        StreamSingleRx, //!< Exposes a single input stream that can be one of the streams of a physical device
        StreamSingleTx, //!< Exposes a single output stream that can be one of the streams of a physical device
        StreamMIMO      //!< May expose any number of input and/or output streams
    };

    enum EngineState {
		StNotStarted,  //!< engine is before initialization
		StIdle,        //!< engine is idle
		StReady,       //!< engine is ready to run
		StRunning,     //!< engine is running
		StError        //!< engine is in error
	};

    DeviceAPI(
        StreamType streamType,
        int deviceTabIndex,
        DSPDeviceSourceEngine *deviceSourceEngine,
        DSPDeviceSinkEngine *deviceSinkEngine,
        DSPDeviceMIMOEngine *deviceMIMOEngine
    );
    ~DeviceAPI();

    // MIMO Engine baseband / channel lists management
    void addSourceStream();
    void removeLastSourceStream();
    void addSinkStream();
    void removeLastSinkStream();

    void addAncillarySink(BasebandSampleSink* sink, unsigned int index = 0);       //!< Adds a sink to receive full baseband and that is not a channel (e.g. spectrum)
    void removeAncillarySink(BasebandSampleSink* sink, unsigned int index = 0);    //!< Removes it
    void setSpectrumSinkInput(bool sourceElseSink = true, unsigned int index = 0); //!< Used in the MIMO case to select which stream is used as input to main spectrum

    void addChannelSink(ThreadedBasebandSampleSink* sink, int streamIndex = 0);        //!< Add a channel sink (Rx)
    void removeChannelSink(ThreadedBasebandSampleSink* sink, int streamIndex = 0);     //!< Remove a channel sink (Rx)
    void addChannelSource(ThreadedBasebandSampleSource* sink, int streamIndex = 0);    //!< Add a channel source (Tx)
    void removeChannelSource(ThreadedBasebandSampleSource* sink, int streamIndex = 0); //!< Remove a channel source (Tx)
    void addMIMOChannel(MIMOChannel* channel);   //!< Add a MIMO channel (n Rx and m Tx combination)
    void removeMIMOChannel(MIMOChannel* channe); //!< Remove a MIMO channel (n Rx and m Tx combination)

    void addChannelSinkAPI(ChannelAPI* channelAPI, int streamIndex = 0);
    void removeChannelSinkAPI(ChannelAPI* channelAPI, int streamIndex = 0);
    void addChannelSourceAPI(ChannelAPI* channelAPI, int streamIndex = 0);
    void removeChannelSourceAPI(ChannelAPI* channelAPI, int streamIndex = 0);
    void addMIMOChannelAPI(ChannelAPI* channelAPI);
    void removeMIMOChannelAPI(ChannelAPI* channelAPI);

    void setSampleSource(DeviceSampleSource* source); //!< Set the device sample source (single Rx)
    void setSampleSink(DeviceSampleSink* sink);       //!< Set the device sample sink (single Tx)
    void setSampleMIMO(DeviceSampleMIMO* mimo);       //!< Set the device sample MIMO
    DeviceSampleSource *getSampleSource();            //!< Return pointer to the device sample source (single Rx) or nullptr
    DeviceSampleSink *getSampleSink();                //!< Return pointer to the device sample sink (single Tx) or nullptr
    DeviceSampleMIMO *getSampleMIMO();                //!< Return pointer to the device sample MIMO or nullptr

    bool initDeviceEngine();    //!< Init the device engine corresponding to the stream type
    bool startDeviceEngine();   //!< Start the device engine corresponding to the stream type
    void stopDeviceEngine();    //!< Stop the device engine corresponding to the stream type
    EngineState state() const;  //!< Return the state of the device engine corresponding to the stream type
    QString errorMessage();     //!< Last error message from the device engine
    uint getDeviceUID() const;  //!< Return the current device engine unique ID

    MessageQueue *getDeviceEngineInputMessageQueue();   //!< Device engine message queue
    MessageQueue *getSamplingDeviceInputMessageQueue(); //!< Sampling device (ex: single Rx) input message queue
    MessageQueue *getSamplingDeviceGUIMessageQueue();   //!< Sampling device (ex: single Tx) GUI input message queue

    void configureCorrections(bool dcOffsetCorrection, bool iqImbalanceCorrection, int streamIndex = 0); //!< Configure current device engine DSP corrections (Rx)

    void setHardwareId(const QString& id);
    void setSamplingDeviceId(const QString& id) { m_samplingDeviceId = id; }
    void resetSamplingDeviceId() { m_samplingDeviceId.clear(); }
    void setSamplingDeviceSerial(const QString& serial) { m_samplingDeviceSerial = serial; }
    void setSamplingDeviceDisplayName(const QString& name) { m_samplingDeviceDisplayName = name; }
    void setSamplingDeviceSequence(int sequence) { m_samplingDeviceSequence = sequence; }
    void setHardwareUserArguments(const QString& userArguments) { m_hardwareUserArguments = userArguments; }
    void setSamplingDevicePluginInterface(PluginInterface *iface);
    void setSamplingDevicePluginInstanceGUI(PluginInstanceGUI *gui);

    const QString& getHardwareId() const { return m_hardwareId; }
    const QString& getSamplingDeviceId() const { return m_samplingDeviceId; }
    const QString& getSamplingDeviceSerial() const { return m_samplingDeviceSerial; }
    const QString& getSamplingDeviceDisplayName() const { return m_samplingDeviceDisplayName; }
    uint32_t getSamplingDeviceSequence() const { return m_samplingDeviceSequence; }
    const QString& getHardwareUserArguments() const { return m_hardwareUserArguments; }

    void setDeviceNbItems(uint32_t nbItems);
    void setDeviceItemIndex(uint32_t index);
    uint32_t getDeviceNbItems() const { return m_deviceNbItems; }
    uint32_t getDeviceItemIndex() const { return m_deviceItemIndex; }

    int getDeviceSetIndex() const { return m_deviceTabIndex; }
    PluginInterface *getPluginInterface() { return m_pluginInterface; }

    PluginInstanceGUI *getSamplingDevicePluginInstanceGUI() { return m_samplingDevicePluginInstanceUI; }
    // PluginInstanceGUI *getSampleSourcePluginInstanceGUI() { return m_sampleSourcePluginInstanceUI; }
    // PluginInstanceGUI *getSampleSinkPluginInstanceGUI() { return m_sampleSinkPluginInstanceUI; }

    void getDeviceEngineStateStr(QString& state);

    ChannelAPI *getChanelSinkAPIAt(int index, int streamIndex = 0);
    ChannelAPI *getChanelSourceAPIAt(int index, int streamIndex = 0);

    int getNbSourceChannels() const { return m_channelSourceAPIs.size(); }
    int getNbSinkChannels() const { return m_channelSinkAPIs.size(); }

    void loadSamplingDeviceSettings(const Preset* preset);
    // void loadSourceSettings(const Preset* preset);
    // void loadSinkSettings(const Preset* preset);
    void saveSamplingDeviceSettings(Preset* preset);
    // void saveSourceSettings(Preset* preset);
    // void saveSinkSettings(Preset* preset);

    DSPDeviceSourceEngine *getDeviceSourceEngine() { return m_deviceSourceEngine; }
    DSPDeviceSinkEngine *getDeviceSinkEngine() { return m_deviceSinkEngine; }

    void addSourceBuddy(DeviceAPI* buddy);
    void addSinkBuddy(DeviceAPI* buddy);
    void removeSourceBuddy(DeviceAPI* buddy);
    void removeSinkBuddy(DeviceAPI* buddy);
    void clearBuddiesLists();
    void *getBuddySharedPtr() const { return m_buddySharedPtr; }
    void setBuddySharedPtr(void *ptr) { m_buddySharedPtr = ptr; }
    bool isBuddyLeader() const { return m_isBuddyLeader; }
    void setBuddyLeader(bool isBuddyLeader) { m_isBuddyLeader = isBuddyLeader; }
    const std::vector<DeviceAPI*>& getSourceBuddies() const { return m_sourceBuddies; }
    const std::vector<DeviceAPI*>& getSinkBuddies() const { return m_sinkBuddies; }

    void setNbSourceStreams(uint32_t nbSourceStreams) { m_nbSourceStreams = nbSourceStreams; }
    void setNbSinkStreams(uint32_t nbSinkStreams) { m_nbSinkStreams = nbSinkStreams; }
    uint32_t getNbSourceStreams() const { return m_nbSourceStreams; }
    uint32_t getNbSinkStreams() const { return m_nbSinkStreams; }

    const QTimer& getMasterTimer() const { return m_masterTimer; } //!< This is the DSPEngine master timer

protected:
    // common

    StreamType m_streamType;
    int m_deviceTabIndex;                //!< This is the tab index in the GUI and also the device set index
    QString m_hardwareId;                //!< The internal id that identifies the type of hardware (i.e. HackRF, BladeRF, ...)
    uint32_t m_deviceNbItems;            //!< Number of items in the physical device either Rx or Tx. Can be >1 for NxM devices (i.e. 2 for LimeSDR)
    uint32_t m_deviceItemIndex;          //!< The item index inb the Rx or Tx side of the physical device. Can be >0 for NxM devices (i.e. 0 or 1 for LimeSDR)
    uint32_t m_nbSourceStreams;          //!< The number of source streams in the logical device. 1 for Single Rx (SI) can be 0 or more for MIMO
    uint32_t m_nbSinkStreams;            //!< The number of sink streams in the logical device. 1 for Single Tx (SO) can be 0 or more for MIMO
    PluginInterface* m_pluginInterface;
    const QTimer& m_masterTimer;         //!< This is the DSPEngine master timer
    QString m_samplingDeviceId;          //!< The internal plugin ID corresponding to the device (i.e. for HackRF input, for HackRF output ...)
    QString m_samplingDeviceSerial;      //!< The device serial number defined by the vendor or a fake one (SDRplay)
    QString m_samplingDeviceDisplayName; //!< The human readable name identifying this instance
    uint32_t m_samplingDeviceSequence;   //!< The device sequence. >0 when more than one device of the same type is connected
    QString m_hardwareUserArguments;     //!< User given arguments to be used at hardware level i.e. for the hardware device and device sequence
    PluginInstanceGUI* m_samplingDevicePluginInstanceUI;

    // Buddies (single Rx or single Tx)

    std::vector<DeviceAPI*> m_sourceBuddies; //!< Device source APIs referencing the same physical device
    std::vector<DeviceAPI*> m_sinkBuddies;   //!< Device sink APIs referencing the same physical device
    void *m_buddySharedPtr;
    bool m_isBuddyLeader;

    // Single Rx (i.e. source)

    DSPDeviceSourceEngine *m_deviceSourceEngine;
    QList<ChannelAPI*> m_channelSinkAPIs;

    // Single Tx (i.e. sink)

    DSPDeviceSinkEngine *m_deviceSinkEngine;
    QList<ChannelAPI*> m_channelSourceAPIs;

    // MIMO

    DSPDeviceMIMOEngine *m_deviceMIMOEngine;
    QList<ChannelAPI*> m_mimoChannelAPIs;

private:
    void renumerateChannels();
};
#endif // SDRBASE_DEVICE_DEVICEAPI_H_