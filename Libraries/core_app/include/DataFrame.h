#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <Data.h>

namespace fby
{
/**
 * @class DataFrame
 *
 * @brief The DataFrame class wraps the data to exchange a video frame within
 * different modules in an application. This class holds a Frame object that
 * contains the necessary data.
 *
 * @callgraph
 * @callergraph
 * @author Andrea Bracci
 * @version 1.0
 * @date 2015
 */
class CORE_APP_EXPORT DataFrame : public Data
{
    Q_OBJECT

public:

    DataFrame();

    /**
     * @brief Clear clears the content of the buffer.
     */
    void Clear();

    /**
     * @return a reference to the Frame object.
     */
    inline Frame& GetFrame()
    {
        return m_Frame;
    }

    /**
     * @return a const reference to the Frame object.
     */
    inline const Frame& GetFrame() const
    {
        return m_Frame;
    }

    /**
     * @return a const reference to the metadata of the member Frame object.
     */
    const Metadata& GetMetadata() const
    {
        return m_Frame.m_Metadata;
    }

    /**
     * @brief SetFrame copies the input buffer to the member buffer along with
     * the frame size info.
     *
     * @param[in]   p_rvBuffer      Input buffer that contains the pixel data.
     * @param[in]   p_iWidth        Frame width.
     * @param[in]   p_iHeight       Frame height.
     * @param[in]   p_iLineWidth    Frame line width.
     */
    void SetFrame(const std::vector<uchar>&     p_rvBuffer,
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
    void SetFrame(uchar*        p_pucBuffer,
                  const int     p_iWidth,
                  const int     p_iHeight,
                  const int     p_iLineWidth);


    /**
     * @brief SetMetadata sets the metadata of this DataFrame.
     *
     * @param[in]   p_rMetadata     Input metadata.
     */
    void SetMetadata(const Metadata& p_rMetadata);

protected:

    Frame   m_Frame;

}; // end class DataFrame.

DEF_PTR(DataFrame);

} // end namespace fby.

DATA_WRAPPER(std::list<fby::Frame>, DataFrameList, m_lFrames);

#endif // DATAFRAME_H
