/**
 * Copyright (c) 2017 Melown Technologies SE
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * *  Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef slpk_reader_hpp_included_
#define slpk_reader_hpp_included_

#include "roarchive/roarchive.hpp"
#include "geometry/mesh.hpp"

#include "./types.hpp"

namespace slpk {


/** SLPK archive reader
 */
class Archive {
public:
    Archive(const boost::filesystem::path &root);

    /** Generic I/O.
     */
    roarchive::IStream::pointer
    istream(const boost::filesystem::path &path) const;

    /** Returns loaded scene layer info.
     */
    const SceneLayerInfo& sceneLayerInfo() const { return sli_; }

    /** Loads node index from given path inside archive.
     */
    Node loadNodeIndex(const boost::filesystem::path &dir) const;

    /** Load root node (from path stated in scene layer info).
     */
    Node loadRootNodeIndex() const;

    /** Loads whole node tree.
     */
    Node::map loadTree() const;

    /** Loads node geometry. Possibly more meshes than just one.
     */
    geometry::Mesh::list loadGeometry(const Node &node) const;

    /** Opens texture file for given geometry mesh. If there are more version of
     *  the same texture the returns PNG or JPEG. DDS is ignored.
     */
    roarchive::IStream::pointer texture(const Node &node, int index = 0)
        const;

private:
    roarchive::RoArchive archive_;
    Metadata metadata_;
    SceneLayerInfo sli_;
};

} // namespace slpk

#endif // slpk_reader_hpp_included_
