/******************************************************************************
 *
 * Copyright (C) 1997-2024 by Dimitri van Heesch.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation under the terms of the GNU General Public License is hereby
 * granted. No representations are made about the suitability of this software
 * for any purpose. It is provided "as is" without express or implied warranty.
 * See the GNU General Public License for more details.
 *
 * Documents produced by Doxygen are derivative works derived from the
 * input used in their production; they are not affected by this license.
 *
 */

#ifndef PLANTUMLSVGPATCHER_H
#define PLANTUMLSVGPATCHER_H

#include "qcstring.h"

/** @brief Utility class to patch PlantUML-generated SVG files.
 *
 *  PlantUML generates SVG files where `\ref` links appear as bare `href="\ref"`
 *  attributes without the reference name. The reference name is contained in
 *  the text content of the `<a>` tag (inside a `<text>` element). This class
 *  extracts those reference names and resolves them to proper URLs.
 */
class PlantumlSvgPatcher
{
  public:
    /** Construct a patcher for the given SVG file.
     *  @param svgFile Full path to the SVG file to patch.
     *  @param relPath Relative path for resolving links.
     *  @param context Context for resolving `\ref` references.
     */
    PlantumlSvgPatcher(const QCString &svgFile, const QCString &relPath, const QCString &context);

    /** Run the patching process.
     *  @return TRUE if successful, FALSE on error.
     */
    bool run();

  private:
    /** Process the SVG content and replace all bare `\ref` links.
     *  @param content The SVG content to process.
     *  @return The patched SVG content.
     */
    QCString patchBareRefs(const QCString &content) const;

    /** Extract the reference name from an anchor tag's text content.
     *  @param anchorContent The content between `<a>` and `</a>` tags.
     *  @return The extracted reference name, or empty string if not found.
     */
    static QCString extractRefNameFromAnchorContent(const QCString &anchorContent);

    /** Resolve a reference name to a URL.
     *  @param refName The reference name to resolve.
     *  @return The resolved URL, or "#" if unresolved.
     */
    QCString resolveRefToUrl(const QCString &refName) const;

    QCString m_svgFile;   //!< Path to the SVG file
    QCString m_relPath;   //!< Relative path for links
    QCString m_context;   //!< Context for ref resolution
};

#endif // PLANTUMLSVGPATCHER_H

