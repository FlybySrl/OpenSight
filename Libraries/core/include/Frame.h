#ifndef FRAME_H
#define FRAME_H

#include <Metadata.h>

namespace fby
{
/**
 * @class Frame
 *
 * @brief The Frame class wraps the data to define a video frame This class
 * holds the following data:
 *
 *  - the buffer that contains the pixel data of the frame;
 *
 *  - the image width (pixels);
 *
 *  - the image height (pixels);
 *
 *  - the linewidth of the image (bytes);
 *
 *  - the metadata to georeference the frame.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_EXPORT Frame
{
public:

    Frame();

    virtual ~Frame();

    /**
     * @brief Clear clears the content of this Frame.
     */
    void Clear();

    /**
     * @return the number of bytes per pixel of this frame.
     */
    size_t GetNumBytesPerPixel() const;

    /**
     * @brief SetFrame copies the input buffer to the member buffer along with
     * the frame size info.
     *
     * @param[in]   p_rvBuffer      Input buffer that contains the pixel data.
     * @param[in]   p_iWidth        Frame width.
     * @param[in]   p_iHeight       Frame height.
     * @param[in]   p_iLineWidth    Frame line width.
     */
    void SetFrame(const std::vector<uint8_t>&   p_rvBuffer,
                  const int                     p_iWidth,
                  const int                     p_iHeight,
                  const int                     p_iLineWidth);

    /**
     * @overload Accepts a raw input pointer to uchar.
     *
     * @warning No check will be performed on the size of the input array of
     * bytes: the user must be sure that it is properly sized.
     *
     * @param[in]   p_pucBuffer     Input buffer that contains the pixel data.
     * @param[in]   p_iWidth        Frame width.
     * @param[in]   p_iHeight       Frame height.
     * @param[in]   p_iLineWidth    Frame line width.
     */
    void SetFrame(uint8_t*      p_pucBuffer,
                  const int     p_iWidth,
                  const int     p_iHeight,
                  const int     p_iLineWidth);

public:

    std::vector<uint8_t>    m_vBuffer;

    int     m_iWidth;
    int     m_iHeight;
    int     m_iLineWidth;

    Metadata    m_Metadata;

}; // end class Frame.

} // end namespace fby.

#endif // FRAME_H
