#ifndef METADATA_H
#define METADATA_H

#include <core_pch.h>

namespace fby
{
/**
 * @class Metadata
 *
 * @brief The Metadata class contains the metadata of an image. Since this class
 * does not depend upon any other structure it is placed in the core library.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_EXPORT Metadata
{
public:

    /**
     * @brief Default constructor.
     */
    Metadata();

    /**
     * @brief Copy constructor.
     *
     * @param[in]   p_rOther    Input Metadata to be copied.
     */
    Metadata(const Metadata& p_rOther);

    /**
     * @brief GetDateTime converts the UNIX timestamp to a human readable
     * date-time.
     *
     * @param[out]  p_riYear            Year.
     * @param[out]  p_riMonth           Month (range: 0 (January) - 11
     *                                  (December)).
     * @param[out]  p_riDay             Month-day (range: 1 - 31).
     * @param[out]  p_riHour            Hour of the day (range: 0 - 23).
     * @param[out]  p_riMinute          Minute of the hour (range: 0 - 59).
     * @param[out]  p_riSeconds         Seconds of the minut (range: 0 - 60
     *                                  since C++11, or 0 - 61 until C++11).
     * @param[out]  p_rdMicroseconds    Microseconds.
     *
     * @return true on successful conversion.
     */
    bool GetDateTime(int&       p_riYear,
                     int&       p_riMonth,
                     int&       p_riDay,
                     int&       p_riHour,
                     int&       p_riMinute,
                     int&       p_riSeconds,
                     double&    p_rdMicroseconds);

    /**
     * @brief Load loads the metadata from a given file.
     *
     * @param[in]   p_rsFile    Input metadata file.
     */
    void Load(const std::string& p_rsFile);

    /**
     * @brief Reset resets this Metadata to its default values.
     */
    void Reset();

    /**
     * @brief Save saves the current metadata to file.
     *
     * @param[in]   p_rsFile    Save file name.
     */
    void Save(const std::string& p_rsFile);

public:

   long long    m_llTimestamp; /*!< UTC MicroSeconds. */

   std::string  m_sMissionID; /*!< Mission ID. */

   std::string  m_sPlatformTailNumber; /*!< Platform tail number. */

   float        m_fPlatformHeading_deg; /*! <Platform Heading [deg]. */

   float        m_fPlatformPitch_deg; /*!< Platform Pitch [deg]. */

   float        m_fPlatformRoll_deg; /*! Platform Roll [deg]. */

   float        m_fPlatformTrueAirSpeed_m_s; /*!< Platform true air-speed [m/s]. */

   std::string  m_sPlatformDesignation; /*!< UAV Number. */

   std::string  m_sImageSourceSensor; /*!< Sensor name. */

   std::string  m_sImageCoordinateSystem; /*!< Geodetic WGS84; Geocentric WGS84;
                                           * UTM; None. */

   double       m_dSensorLat_deg; /*!< Sensor Latitude [deg]. */

   double       m_dSensorLon_deg; /*!< Sensor Longitude [deg]. */

   double       m_dSensorAlt_m; /*!< Sensor Altitude [m]. */

   float        m_fSensorHFOV_deg; /*!< Sensor HFOV [deg]. */

   float        m_fSensorVFOV_deg; /*!< Sensor VFOV [deg]. */

   float        m_fSensorAzimuth_deg; /*!< Sensor Azimut [deg]. */

   float        m_fSensorElevation_deg; /*!< Sensor Elevation [deg]. */

   float        m_fSensorRoll_deg; /*!< Sensor Roll [deg]. */

   float        m_fSlantRange_m; /*!< Slant Range [m]. */

   float        m_fTargetWidth_m; /*!< Linear ground distance between the
                                   * centers of both side of the captured image
                                   * [m]. */

   double       m_dFrameCenterLat_deg; /*!< Center Frame Latitude [deg]. */

   double       m_dFrameCenterLon_deg; /*!< Center Frame Longitude [deg]. */

   double       m_dFrameCenterAlt_m; /*!< Center Frame Altitude [m]. */

   float        m_fWindDirection_deg; /*!< Wind Direction [deg]. */

   float        m_fWindSpeed_m_s; /*!< Wind Speed [m/s]. */

   std::string  m_sPlatformCallSign; /*!< Platform call-sign. */

}; // end class Metadata.

} // end namespace fby.

#endif // METADATA_H
