/**
 * SDRangel
 * This is the web REST/JSON API of SDRangel SDR software. SDRangel is an Open Source Qt5/OpenGL 3.0+ (4.3+ in Windows) GUI and server Software Defined Radio and signal analyzer in software. It supports Airspy, BladeRF, HackRF, LimeSDR, PlutoSDR, RTL-SDR, SDRplay RSP1 and FunCube    ---   Limitations and specifcities:    * In SDRangel GUI the first Rx device set cannot be deleted. Conversely the server starts with no device sets and its number of device sets can be reduced to zero by as many calls as necessary to /sdrangel/deviceset with DELETE method.   * Preset import and export from/to file is a server only feature.   * Device set focus is a GUI only feature.   * The following channels are not implemented (status 501 is returned): ATV and DATV demodulators, Channel Analyzer NG, LoRa demodulator   * The device settings and report structures contains only the sub-structure corresponding to the device type. The DeviceSettings and DeviceReport structures documented here shows all of them but only one will be or should be present at a time   * The channel settings and report structures contains only the sub-structure corresponding to the channel type. The ChannelSettings and ChannelReport structures documented here shows all of them but only one will be or should be present at a time    --- 
 *
 * OpenAPI spec version: 7.0.0
 * Contact: f4exb06@gmail.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */


#include "SWGILSDemodSettings.h"

#include "SWGHelpers.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

namespace SWGSDRangel {

SWGILSDemodSettings::SWGILSDemodSettings(QString* json) {
    init();
    this->fromJson(*json);
}

SWGILSDemodSettings::SWGILSDemodSettings() {
    input_frequency_offset = 0L;
    m_input_frequency_offset_isSet = false;
    rf_bandwidth = 0.0f;
    m_rf_bandwidth_isSet = false;
    mode = 0;
    m_mode_isSet = false;
    frequency_index = 0;
    m_frequency_index_isSet = false;
    squelch = 0;
    m_squelch_isSet = false;
    volume = 0.0f;
    m_volume_isSet = false;
    audio_mute = 0;
    m_audio_mute_isSet = false;
    average = 0;
    m_average_isSet = false;
    ddm_units = 0;
    m_ddm_units_isSet = false;
    ident_threshold = 0.0f;
    m_ident_threshold_isSet = false;
    ident = nullptr;
    m_ident_isSet = false;
    runway = nullptr;
    m_runway_isSet = false;
    true_bearing = 0.0f;
    m_true_bearing_isSet = false;
    latitude = nullptr;
    m_latitude_isSet = false;
    longitude = nullptr;
    m_longitude_isSet = false;
    elevation = 0;
    m_elevation_isSet = false;
    glide_path = 0.0f;
    m_glide_path_isSet = false;
    ref_height = 0.0f;
    m_ref_height_isSet = false;
    course_width = 0.0f;
    m_course_width_isSet = false;
    udp_enabled = 0;
    m_udp_enabled_isSet = false;
    udp_address = nullptr;
    m_udp_address_isSet = false;
    udp_port = 0;
    m_udp_port_isSet = false;
    log_filename = nullptr;
    m_log_filename_isSet = false;
    log_enabled = 0;
    m_log_enabled_isSet = false;
    rgb_color = 0;
    m_rgb_color_isSet = false;
    title = nullptr;
    m_title_isSet = false;
    stream_index = 0;
    m_stream_index_isSet = false;
    use_reverse_api = 0;
    m_use_reverse_api_isSet = false;
    reverse_api_address = nullptr;
    m_reverse_api_address_isSet = false;
    reverse_api_port = 0;
    m_reverse_api_port_isSet = false;
    reverse_api_device_index = 0;
    m_reverse_api_device_index_isSet = false;
    reverse_api_channel_index = 0;
    m_reverse_api_channel_index_isSet = false;
    scope_config = nullptr;
    m_scope_config_isSet = false;
    channel_marker = nullptr;
    m_channel_marker_isSet = false;
    rollup_state = nullptr;
    m_rollup_state_isSet = false;
}

SWGILSDemodSettings::~SWGILSDemodSettings() {
    this->cleanup();
}

void
SWGILSDemodSettings::init() {
    input_frequency_offset = 0L;
    m_input_frequency_offset_isSet = false;
    rf_bandwidth = 0.0f;
    m_rf_bandwidth_isSet = false;
    mode = 0;
    m_mode_isSet = false;
    frequency_index = 0;
    m_frequency_index_isSet = false;
    squelch = 0;
    m_squelch_isSet = false;
    volume = 0.0f;
    m_volume_isSet = false;
    audio_mute = 0;
    m_audio_mute_isSet = false;
    average = 0;
    m_average_isSet = false;
    ddm_units = 0;
    m_ddm_units_isSet = false;
    ident_threshold = 0.0f;
    m_ident_threshold_isSet = false;
    ident = new QString("");
    m_ident_isSet = false;
    runway = new QString("");
    m_runway_isSet = false;
    true_bearing = 0.0f;
    m_true_bearing_isSet = false;
    latitude = new QString("");
    m_latitude_isSet = false;
    longitude = new QString("");
    m_longitude_isSet = false;
    elevation = 0;
    m_elevation_isSet = false;
    glide_path = 0.0f;
    m_glide_path_isSet = false;
    ref_height = 0.0f;
    m_ref_height_isSet = false;
    course_width = 0.0f;
    m_course_width_isSet = false;
    udp_enabled = 0;
    m_udp_enabled_isSet = false;
    udp_address = new QString("");
    m_udp_address_isSet = false;
    udp_port = 0;
    m_udp_port_isSet = false;
    log_filename = new QString("");
    m_log_filename_isSet = false;
    log_enabled = 0;
    m_log_enabled_isSet = false;
    rgb_color = 0;
    m_rgb_color_isSet = false;
    title = new QString("");
    m_title_isSet = false;
    stream_index = 0;
    m_stream_index_isSet = false;
    use_reverse_api = 0;
    m_use_reverse_api_isSet = false;
    reverse_api_address = new QString("");
    m_reverse_api_address_isSet = false;
    reverse_api_port = 0;
    m_reverse_api_port_isSet = false;
    reverse_api_device_index = 0;
    m_reverse_api_device_index_isSet = false;
    reverse_api_channel_index = 0;
    m_reverse_api_channel_index_isSet = false;
    scope_config = new SWGGLScope();
    m_scope_config_isSet = false;
    channel_marker = new SWGChannelMarker();
    m_channel_marker_isSet = false;
    rollup_state = new SWGRollupState();
    m_rollup_state_isSet = false;
}

void
SWGILSDemodSettings::cleanup() {










    if(ident != nullptr) { 
        delete ident;
    }
    if(runway != nullptr) { 
        delete runway;
    }

    if(latitude != nullptr) { 
        delete latitude;
    }
    if(longitude != nullptr) { 
        delete longitude;
    }





    if(udp_address != nullptr) { 
        delete udp_address;
    }

    if(log_filename != nullptr) { 
        delete log_filename;
    }


    if(title != nullptr) { 
        delete title;
    }


    if(reverse_api_address != nullptr) { 
        delete reverse_api_address;
    }



    if(scope_config != nullptr) { 
        delete scope_config;
    }
    if(channel_marker != nullptr) { 
        delete channel_marker;
    }
    if(rollup_state != nullptr) { 
        delete rollup_state;
    }
}

SWGILSDemodSettings*
SWGILSDemodSettings::fromJson(QString &json) {
    QByteArray array (json.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
    return this;
}

void
SWGILSDemodSettings::fromJsonObject(QJsonObject &pJson) {
    ::SWGSDRangel::setValue(&input_frequency_offset, pJson["inputFrequencyOffset"], "qint64", "");
    
    ::SWGSDRangel::setValue(&rf_bandwidth, pJson["rfBandwidth"], "float", "");
    
    ::SWGSDRangel::setValue(&mode, pJson["mode"], "qint32", "");
    
    ::SWGSDRangel::setValue(&frequency_index, pJson["frequencyIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&squelch, pJson["squelch"], "qint32", "");
    
    ::SWGSDRangel::setValue(&volume, pJson["volume"], "float", "");
    
    ::SWGSDRangel::setValue(&audio_mute, pJson["audioMute"], "qint32", "");
    
    ::SWGSDRangel::setValue(&average, pJson["average"], "qint32", "");
    
    ::SWGSDRangel::setValue(&ddm_units, pJson["ddmUnits"], "qint32", "");
    
    ::SWGSDRangel::setValue(&ident_threshold, pJson["identThreshold"], "float", "");
    
    ::SWGSDRangel::setValue(&ident, pJson["ident"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&runway, pJson["runway"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&true_bearing, pJson["trueBearing"], "float", "");
    
    ::SWGSDRangel::setValue(&latitude, pJson["latitude"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&longitude, pJson["longitude"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&elevation, pJson["elevation"], "qint32", "");
    
    ::SWGSDRangel::setValue(&glide_path, pJson["glidePath"], "float", "");
    
    ::SWGSDRangel::setValue(&ref_height, pJson["refHeight"], "float", "");
    
    ::SWGSDRangel::setValue(&course_width, pJson["courseWidth"], "float", "");
    
    ::SWGSDRangel::setValue(&udp_enabled, pJson["udpEnabled"], "qint32", "");
    
    ::SWGSDRangel::setValue(&udp_address, pJson["udpAddress"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&udp_port, pJson["udpPort"], "qint32", "");
    
    ::SWGSDRangel::setValue(&log_filename, pJson["logFilename"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&log_enabled, pJson["logEnabled"], "qint32", "");
    
    ::SWGSDRangel::setValue(&rgb_color, pJson["rgbColor"], "qint32", "");
    
    ::SWGSDRangel::setValue(&title, pJson["title"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&stream_index, pJson["streamIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&use_reverse_api, pJson["useReverseAPI"], "qint32", "");
    
    ::SWGSDRangel::setValue(&reverse_api_address, pJson["reverseAPIAddress"], "QString", "QString");
    
    ::SWGSDRangel::setValue(&reverse_api_port, pJson["reverseAPIPort"], "qint32", "");
    
    ::SWGSDRangel::setValue(&reverse_api_device_index, pJson["reverseAPIDeviceIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&reverse_api_channel_index, pJson["reverseAPIChannelIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&scope_config, pJson["scopeConfig"], "SWGGLScope", "SWGGLScope");
    
    ::SWGSDRangel::setValue(&channel_marker, pJson["channelMarker"], "SWGChannelMarker", "SWGChannelMarker");
    
    ::SWGSDRangel::setValue(&rollup_state, pJson["rollupState"], "SWGRollupState", "SWGRollupState");
    
}

QString
SWGILSDemodSettings::asJson ()
{
    QJsonObject* obj = this->asJsonObject();

    QJsonDocument doc(*obj);
    QByteArray bytes = doc.toJson();
    delete obj;
    return QString(bytes);
}

QJsonObject*
SWGILSDemodSettings::asJsonObject() {
    QJsonObject* obj = new QJsonObject();
    if(m_input_frequency_offset_isSet){
        obj->insert("inputFrequencyOffset", QJsonValue(input_frequency_offset));
    }
    if(m_rf_bandwidth_isSet){
        obj->insert("rfBandwidth", QJsonValue(rf_bandwidth));
    }
    if(m_mode_isSet){
        obj->insert("mode", QJsonValue(mode));
    }
    if(m_frequency_index_isSet){
        obj->insert("frequencyIndex", QJsonValue(frequency_index));
    }
    if(m_squelch_isSet){
        obj->insert("squelch", QJsonValue(squelch));
    }
    if(m_volume_isSet){
        obj->insert("volume", QJsonValue(volume));
    }
    if(m_audio_mute_isSet){
        obj->insert("audioMute", QJsonValue(audio_mute));
    }
    if(m_average_isSet){
        obj->insert("average", QJsonValue(average));
    }
    if(m_ddm_units_isSet){
        obj->insert("ddmUnits", QJsonValue(ddm_units));
    }
    if(m_ident_threshold_isSet){
        obj->insert("identThreshold", QJsonValue(ident_threshold));
    }
    if(ident != nullptr && *ident != QString("")){
        toJsonValue(QString("ident"), ident, obj, QString("QString"));
    }
    if(runway != nullptr && *runway != QString("")){
        toJsonValue(QString("runway"), runway, obj, QString("QString"));
    }
    if(m_true_bearing_isSet){
        obj->insert("trueBearing", QJsonValue(true_bearing));
    }
    if(latitude != nullptr && *latitude != QString("")){
        toJsonValue(QString("latitude"), latitude, obj, QString("QString"));
    }
    if(longitude != nullptr && *longitude != QString("")){
        toJsonValue(QString("longitude"), longitude, obj, QString("QString"));
    }
    if(m_elevation_isSet){
        obj->insert("elevation", QJsonValue(elevation));
    }
    if(m_glide_path_isSet){
        obj->insert("glidePath", QJsonValue(glide_path));
    }
    if(m_ref_height_isSet){
        obj->insert("refHeight", QJsonValue(ref_height));
    }
    if(m_course_width_isSet){
        obj->insert("courseWidth", QJsonValue(course_width));
    }
    if(m_udp_enabled_isSet){
        obj->insert("udpEnabled", QJsonValue(udp_enabled));
    }
    if(udp_address != nullptr && *udp_address != QString("")){
        toJsonValue(QString("udpAddress"), udp_address, obj, QString("QString"));
    }
    if(m_udp_port_isSet){
        obj->insert("udpPort", QJsonValue(udp_port));
    }
    if(log_filename != nullptr && *log_filename != QString("")){
        toJsonValue(QString("logFilename"), log_filename, obj, QString("QString"));
    }
    if(m_log_enabled_isSet){
        obj->insert("logEnabled", QJsonValue(log_enabled));
    }
    if(m_rgb_color_isSet){
        obj->insert("rgbColor", QJsonValue(rgb_color));
    }
    if(title != nullptr && *title != QString("")){
        toJsonValue(QString("title"), title, obj, QString("QString"));
    }
    if(m_stream_index_isSet){
        obj->insert("streamIndex", QJsonValue(stream_index));
    }
    if(m_use_reverse_api_isSet){
        obj->insert("useReverseAPI", QJsonValue(use_reverse_api));
    }
    if(reverse_api_address != nullptr && *reverse_api_address != QString("")){
        toJsonValue(QString("reverseAPIAddress"), reverse_api_address, obj, QString("QString"));
    }
    if(m_reverse_api_port_isSet){
        obj->insert("reverseAPIPort", QJsonValue(reverse_api_port));
    }
    if(m_reverse_api_device_index_isSet){
        obj->insert("reverseAPIDeviceIndex", QJsonValue(reverse_api_device_index));
    }
    if(m_reverse_api_channel_index_isSet){
        obj->insert("reverseAPIChannelIndex", QJsonValue(reverse_api_channel_index));
    }
    if((scope_config != nullptr) && (scope_config->isSet())){
        toJsonValue(QString("scopeConfig"), scope_config, obj, QString("SWGGLScope"));
    }
    if((channel_marker != nullptr) && (channel_marker->isSet())){
        toJsonValue(QString("channelMarker"), channel_marker, obj, QString("SWGChannelMarker"));
    }
    if((rollup_state != nullptr) && (rollup_state->isSet())){
        toJsonValue(QString("rollupState"), rollup_state, obj, QString("SWGRollupState"));
    }

    return obj;
}

qint64
SWGILSDemodSettings::getInputFrequencyOffset() {
    return input_frequency_offset;
}
void
SWGILSDemodSettings::setInputFrequencyOffset(qint64 input_frequency_offset) {
    this->input_frequency_offset = input_frequency_offset;
    this->m_input_frequency_offset_isSet = true;
}

float
SWGILSDemodSettings::getRfBandwidth() {
    return rf_bandwidth;
}
void
SWGILSDemodSettings::setRfBandwidth(float rf_bandwidth) {
    this->rf_bandwidth = rf_bandwidth;
    this->m_rf_bandwidth_isSet = true;
}

qint32
SWGILSDemodSettings::getMode() {
    return mode;
}
void
SWGILSDemodSettings::setMode(qint32 mode) {
    this->mode = mode;
    this->m_mode_isSet = true;
}

qint32
SWGILSDemodSettings::getFrequencyIndex() {
    return frequency_index;
}
void
SWGILSDemodSettings::setFrequencyIndex(qint32 frequency_index) {
    this->frequency_index = frequency_index;
    this->m_frequency_index_isSet = true;
}

qint32
SWGILSDemodSettings::getSquelch() {
    return squelch;
}
void
SWGILSDemodSettings::setSquelch(qint32 squelch) {
    this->squelch = squelch;
    this->m_squelch_isSet = true;
}

float
SWGILSDemodSettings::getVolume() {
    return volume;
}
void
SWGILSDemodSettings::setVolume(float volume) {
    this->volume = volume;
    this->m_volume_isSet = true;
}

qint32
SWGILSDemodSettings::getAudioMute() {
    return audio_mute;
}
void
SWGILSDemodSettings::setAudioMute(qint32 audio_mute) {
    this->audio_mute = audio_mute;
    this->m_audio_mute_isSet = true;
}

qint32
SWGILSDemodSettings::getAverage() {
    return average;
}
void
SWGILSDemodSettings::setAverage(qint32 average) {
    this->average = average;
    this->m_average_isSet = true;
}

qint32
SWGILSDemodSettings::getDdmUnits() {
    return ddm_units;
}
void
SWGILSDemodSettings::setDdmUnits(qint32 ddm_units) {
    this->ddm_units = ddm_units;
    this->m_ddm_units_isSet = true;
}

float
SWGILSDemodSettings::getIdentThreshold() {
    return ident_threshold;
}
void
SWGILSDemodSettings::setIdentThreshold(float ident_threshold) {
    this->ident_threshold = ident_threshold;
    this->m_ident_threshold_isSet = true;
}

QString*
SWGILSDemodSettings::getIdent() {
    return ident;
}
void
SWGILSDemodSettings::setIdent(QString* ident) {
    this->ident = ident;
    this->m_ident_isSet = true;
}

QString*
SWGILSDemodSettings::getRunway() {
    return runway;
}
void
SWGILSDemodSettings::setRunway(QString* runway) {
    this->runway = runway;
    this->m_runway_isSet = true;
}

float
SWGILSDemodSettings::getTrueBearing() {
    return true_bearing;
}
void
SWGILSDemodSettings::setTrueBearing(float true_bearing) {
    this->true_bearing = true_bearing;
    this->m_true_bearing_isSet = true;
}

QString*
SWGILSDemodSettings::getLatitude() {
    return latitude;
}
void
SWGILSDemodSettings::setLatitude(QString* latitude) {
    this->latitude = latitude;
    this->m_latitude_isSet = true;
}

QString*
SWGILSDemodSettings::getLongitude() {
    return longitude;
}
void
SWGILSDemodSettings::setLongitude(QString* longitude) {
    this->longitude = longitude;
    this->m_longitude_isSet = true;
}

qint32
SWGILSDemodSettings::getElevation() {
    return elevation;
}
void
SWGILSDemodSettings::setElevation(qint32 elevation) {
    this->elevation = elevation;
    this->m_elevation_isSet = true;
}

float
SWGILSDemodSettings::getGlidePath() {
    return glide_path;
}
void
SWGILSDemodSettings::setGlidePath(float glide_path) {
    this->glide_path = glide_path;
    this->m_glide_path_isSet = true;
}

float
SWGILSDemodSettings::getRefHeight() {
    return ref_height;
}
void
SWGILSDemodSettings::setRefHeight(float ref_height) {
    this->ref_height = ref_height;
    this->m_ref_height_isSet = true;
}

float
SWGILSDemodSettings::getCourseWidth() {
    return course_width;
}
void
SWGILSDemodSettings::setCourseWidth(float course_width) {
    this->course_width = course_width;
    this->m_course_width_isSet = true;
}

qint32
SWGILSDemodSettings::getUdpEnabled() {
    return udp_enabled;
}
void
SWGILSDemodSettings::setUdpEnabled(qint32 udp_enabled) {
    this->udp_enabled = udp_enabled;
    this->m_udp_enabled_isSet = true;
}

QString*
SWGILSDemodSettings::getUdpAddress() {
    return udp_address;
}
void
SWGILSDemodSettings::setUdpAddress(QString* udp_address) {
    this->udp_address = udp_address;
    this->m_udp_address_isSet = true;
}

qint32
SWGILSDemodSettings::getUdpPort() {
    return udp_port;
}
void
SWGILSDemodSettings::setUdpPort(qint32 udp_port) {
    this->udp_port = udp_port;
    this->m_udp_port_isSet = true;
}

QString*
SWGILSDemodSettings::getLogFilename() {
    return log_filename;
}
void
SWGILSDemodSettings::setLogFilename(QString* log_filename) {
    this->log_filename = log_filename;
    this->m_log_filename_isSet = true;
}

qint32
SWGILSDemodSettings::getLogEnabled() {
    return log_enabled;
}
void
SWGILSDemodSettings::setLogEnabled(qint32 log_enabled) {
    this->log_enabled = log_enabled;
    this->m_log_enabled_isSet = true;
}

qint32
SWGILSDemodSettings::getRgbColor() {
    return rgb_color;
}
void
SWGILSDemodSettings::setRgbColor(qint32 rgb_color) {
    this->rgb_color = rgb_color;
    this->m_rgb_color_isSet = true;
}

QString*
SWGILSDemodSettings::getTitle() {
    return title;
}
void
SWGILSDemodSettings::setTitle(QString* title) {
    this->title = title;
    this->m_title_isSet = true;
}

qint32
SWGILSDemodSettings::getStreamIndex() {
    return stream_index;
}
void
SWGILSDemodSettings::setStreamIndex(qint32 stream_index) {
    this->stream_index = stream_index;
    this->m_stream_index_isSet = true;
}

qint32
SWGILSDemodSettings::getUseReverseApi() {
    return use_reverse_api;
}
void
SWGILSDemodSettings::setUseReverseApi(qint32 use_reverse_api) {
    this->use_reverse_api = use_reverse_api;
    this->m_use_reverse_api_isSet = true;
}

QString*
SWGILSDemodSettings::getReverseApiAddress() {
    return reverse_api_address;
}
void
SWGILSDemodSettings::setReverseApiAddress(QString* reverse_api_address) {
    this->reverse_api_address = reverse_api_address;
    this->m_reverse_api_address_isSet = true;
}

qint32
SWGILSDemodSettings::getReverseApiPort() {
    return reverse_api_port;
}
void
SWGILSDemodSettings::setReverseApiPort(qint32 reverse_api_port) {
    this->reverse_api_port = reverse_api_port;
    this->m_reverse_api_port_isSet = true;
}

qint32
SWGILSDemodSettings::getReverseApiDeviceIndex() {
    return reverse_api_device_index;
}
void
SWGILSDemodSettings::setReverseApiDeviceIndex(qint32 reverse_api_device_index) {
    this->reverse_api_device_index = reverse_api_device_index;
    this->m_reverse_api_device_index_isSet = true;
}

qint32
SWGILSDemodSettings::getReverseApiChannelIndex() {
    return reverse_api_channel_index;
}
void
SWGILSDemodSettings::setReverseApiChannelIndex(qint32 reverse_api_channel_index) {
    this->reverse_api_channel_index = reverse_api_channel_index;
    this->m_reverse_api_channel_index_isSet = true;
}

SWGGLScope*
SWGILSDemodSettings::getScopeConfig() {
    return scope_config;
}
void
SWGILSDemodSettings::setScopeConfig(SWGGLScope* scope_config) {
    this->scope_config = scope_config;
    this->m_scope_config_isSet = true;
}

SWGChannelMarker*
SWGILSDemodSettings::getChannelMarker() {
    return channel_marker;
}
void
SWGILSDemodSettings::setChannelMarker(SWGChannelMarker* channel_marker) {
    this->channel_marker = channel_marker;
    this->m_channel_marker_isSet = true;
}

SWGRollupState*
SWGILSDemodSettings::getRollupState() {
    return rollup_state;
}
void
SWGILSDemodSettings::setRollupState(SWGRollupState* rollup_state) {
    this->rollup_state = rollup_state;
    this->m_rollup_state_isSet = true;
}


bool
SWGILSDemodSettings::isSet(){
    bool isObjectUpdated = false;
    do{
        if(m_input_frequency_offset_isSet){
            isObjectUpdated = true; break;
        }
        if(m_rf_bandwidth_isSet){
            isObjectUpdated = true; break;
        }
        if(m_mode_isSet){
            isObjectUpdated = true; break;
        }
        if(m_frequency_index_isSet){
            isObjectUpdated = true; break;
        }
        if(m_squelch_isSet){
            isObjectUpdated = true; break;
        }
        if(m_volume_isSet){
            isObjectUpdated = true; break;
        }
        if(m_audio_mute_isSet){
            isObjectUpdated = true; break;
        }
        if(m_average_isSet){
            isObjectUpdated = true; break;
        }
        if(m_ddm_units_isSet){
            isObjectUpdated = true; break;
        }
        if(m_ident_threshold_isSet){
            isObjectUpdated = true; break;
        }
        if(ident && *ident != QString("")){
            isObjectUpdated = true; break;
        }
        if(runway && *runway != QString("")){
            isObjectUpdated = true; break;
        }
        if(m_true_bearing_isSet){
            isObjectUpdated = true; break;
        }
        if(latitude && *latitude != QString("")){
            isObjectUpdated = true; break;
        }
        if(longitude && *longitude != QString("")){
            isObjectUpdated = true; break;
        }
        if(m_elevation_isSet){
            isObjectUpdated = true; break;
        }
        if(m_glide_path_isSet){
            isObjectUpdated = true; break;
        }
        if(m_ref_height_isSet){
            isObjectUpdated = true; break;
        }
        if(m_course_width_isSet){
            isObjectUpdated = true; break;
        }
        if(m_udp_enabled_isSet){
            isObjectUpdated = true; break;
        }
        if(udp_address && *udp_address != QString("")){
            isObjectUpdated = true; break;
        }
        if(m_udp_port_isSet){
            isObjectUpdated = true; break;
        }
        if(log_filename && *log_filename != QString("")){
            isObjectUpdated = true; break;
        }
        if(m_log_enabled_isSet){
            isObjectUpdated = true; break;
        }
        if(m_rgb_color_isSet){
            isObjectUpdated = true; break;
        }
        if(title && *title != QString("")){
            isObjectUpdated = true; break;
        }
        if(m_stream_index_isSet){
            isObjectUpdated = true; break;
        }
        if(m_use_reverse_api_isSet){
            isObjectUpdated = true; break;
        }
        if(reverse_api_address && *reverse_api_address != QString("")){
            isObjectUpdated = true; break;
        }
        if(m_reverse_api_port_isSet){
            isObjectUpdated = true; break;
        }
        if(m_reverse_api_device_index_isSet){
            isObjectUpdated = true; break;
        }
        if(m_reverse_api_channel_index_isSet){
            isObjectUpdated = true; break;
        }
        if(scope_config && scope_config->isSet()){
            isObjectUpdated = true; break;
        }
        if(channel_marker && channel_marker->isSet()){
            isObjectUpdated = true; break;
        }
        if(rollup_state && rollup_state->isSet()){
            isObjectUpdated = true; break;
        }
    }while(false);
    return isObjectUpdated;
}
}

