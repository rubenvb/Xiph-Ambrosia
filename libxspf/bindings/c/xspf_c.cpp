/*
 * xspf_c - Simple C interface for libxspf
 *
 * Copyright (C) 2007, Ed Schouten / Xiph.Org Foundation
 * Copyright (C) 2008, Sebastian Pipping / Xiph.Org Foundation
 * All rights reserved.
 *
 * Redistribution  and use in source and binary forms, with or without
 * modification,  are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions   of  source  code  must  retain  the   above
 *       copyright  notice, this list of conditions and the  following
 *       disclaimer.
 *
 *     * Redistributions  in  binary  form must  reproduce  the  above
 *       copyright  notice, this list of conditions and the  following
 *       disclaimer   in  the  documentation  and/or  other  materials
 *       provided with the distribution.
 *
 *     * Neither  the name of the Xiph.Org Foundation nor the names of
 *       its  contributors may be used to endorse or promote  products
 *       derived  from  this software without specific  prior  written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT  NOT
 * LIMITED  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS
 * FOR  A  PARTICULAR  PURPOSE ARE DISCLAIMED. IN NO EVENT  SHALL  THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL,    SPECIAL,   EXEMPLARY,   OR   CONSEQUENTIAL   DAMAGES
 * (INCLUDING,  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES;  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT  LIABILITY,  OR  TORT (INCLUDING  NEGLIGENCE  OR  OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Ed Schouten <ed@fxq.nl>
 * Sebastian Pipping <sping@xiph.org>
 */
/**
 * @file xspf_c.cpp
 * @brief Simple libxspf C bindings.
 */

#include <xspf/XspfIndentFormatter.h>
#include <xspf/XspfProps.h>
#include <xspf/XspfReader.h>
#include <xspf/XspfReaderCallback.h>
#include <xspf/XspfTrack.h>
#include <xspf/XspfWriter.h>
#include <cstring>

extern "C" {
#include "xspf_c.h"
}

using namespace Xspf;

/**
 * @brief Xspf list reading callback, which stores data in a specific
 *        C-style Xspf list.
 */
class XspfCReaderCallback : public XspfReaderCallback {
private:
	/**
	 * @brief The C-style Xspf list the tracks should be appended
	 *        to.
	 */
	xspf_list *list;
	/**
	 * @brief Pointer to the `next' field in the last inserted item
	 *        for improving append speed.
	 */
	xspf_track **newtrack;

	/**
	 * @brief Callback which adds tracks to the xspf_list.
	 */
	void addTrack(XspfTrack *track);
	/**
	 * @brief Callback which sets properties in the xspf_list.
	 */
	void setProps(XspfProps *props);
public:
	/**
	 * @brief Create callback interface for filling a xspf_list.
	 */
	XspfCReaderCallback(xspf_list *list);
	/**
	 * @brief Finalize the xspf_list.
	 */
	virtual ~XspfCReaderCallback();
};

XspfCReaderCallback::XspfCReaderCallback(xspf_list *list)
{
	this->list = list;
	newtrack = &list->tracks;
}

XspfCReaderCallback::~XspfCReaderCallback()
{
	/* Null-terminate the tracks list */
	*newtrack = NULL;
}

void
XspfCReaderCallback::addTrack(XspfTrack *track)
{
	xspf_mvalue **newmv;
	char *str;

	/* Append new item to the track list */
	*newtrack = new xspf_track;

	(*newtrack)->creator = track->stealCreator();
	(*newtrack)->title = track->stealTitle();
	(*newtrack)->album = track->stealAlbum();
	(*newtrack)->duration = track->getDuration();
	(*newtrack)->tracknum = track->getTrackNum();
	(*newtrack)->pdata = NULL;

	/* Locations */
	newmv = &(*newtrack)->locations;
	while ((str = track->stealFirstLocation()) != NULL) {
		*newmv = new xspf_mvalue;
		(*newmv)->value = str;
		(*newmv)->pdata = NULL;

		/* On to the next location */
		newmv = &(*newmv)->next;
	}
	*newmv = NULL;

	/* Identifiers */
	newmv = &(*newtrack)->identifiers;
	while ((str = track->stealFirstIdentifier()) != NULL) {
		*newmv = new xspf_mvalue;
		(*newmv)->value = str;
		(*newmv)->pdata = NULL;

		/* On to the next location */
		newmv = &(*newmv)->next;
	}
	*newmv = NULL;

	/* Clean up and move to the next track */
	delete track;
	newtrack = &(*newtrack)->next;
}

void
XspfCReaderCallback::setProps(XspfProps *props)
{
	list->license = props->stealLicense();
	list->location = props->stealLocation();
	list->identifier = props->stealIdentifier();

	delete props;
}

/**
 * @brief Deallocate all objects in a xspf_mvalue linked list.
 */
static void
xspf_mvalue_free(struct xspf_mvalue *mv)
{
	struct xspf_mvalue *nmv;

	for (; mv != NULL; mv = nmv) {
		/* Back-up pointer */
		nmv = mv->next;
		delete [] mv->value;
		delete mv;
	}
}

/*
 * Public C interface
 */

extern "C" struct xspf_list *
xspf_parse(char const *filename, char const *baseuri)
{
	XspfReader read;
	xspf_list *ret;

	/* Allocate empty playlist */
	ret = new xspf_list;

	/* Fill the list with parser results */
	XspfCReaderCallback readcb(ret);
	if (read.parseFile(filename, &readcb, baseuri) == XSPF_READER_SUCCESS) {
		/* Success */
		return (ret);
	} else {
		/* Malformed/non-existent list */
		delete ret;
		return (NULL);
	}
}

extern "C" struct xspf_list *
xspf_parse_memory(char const *memory, int len_bytes, char const *baseuri)
{
	XspfReader read;
	xspf_list *ret;

	/* Allocate empty playlist */
	ret = new xspf_list;

	/* Fill the list with parser results */
	XspfCReaderCallback readcb(ret);
	if (read.parseMemory(memory, len_bytes, &readcb, baseuri) == XSPF_READER_SUCCESS) {
		/* Success */
		return (ret);
	} else {
		/* Malformed/non-existent list */
		delete ret;
		return (NULL);
	}
}

extern "C" struct xspf_list *
xspf_new(void)
{
	xspf_list *ret;

	ret = new xspf_list;
	ret->license = NULL;
	ret->location = NULL;
	ret->identifier = NULL;
	ret->tracks = NULL;
	ret->pdata = NULL;

	return (ret);
}

extern "C" void
xspf_free(struct xspf_list *list)
{
	xspf_track *tr, *ntr;

	delete [] list->license;
	delete [] list->location;
	delete [] list->identifier;

	for (tr = list->tracks; tr != NULL; tr = ntr) {
		/* Back-up pointer */
		ntr = tr->next;

		delete [] tr->creator;
		delete [] tr->title;
		delete [] tr->album;

		xspf_mvalue_free(tr->locations);
		xspf_mvalue_free(tr->identifiers);

		delete tr;
	}

	delete list;
}

extern "C" void
xspf_setvalue(char **str, char const *nstr)
{
	/* Delete old string */
	delete [] *str;

	if (nstr == NULL) {
		/* Unset value */
		*str = NULL;
	} else {
		/* Copy value */
		size_t len;
		len = strlen(nstr) + 1;
		*str = new char[len];
		strcpy(*str, nstr);
	}
}

extern "C" struct xspf_mvalue *
xspf_new_mvalue_before(struct xspf_mvalue **mvalue)
{
	xspf_mvalue *ret;

	ret = new xspf_mvalue;
	ret->value = NULL;
	ret->pdata = NULL;
	ret->next = *mvalue;
	*mvalue = ret;

	return (ret);
}

extern "C" struct xspf_track *
xspf_new_track_before(struct xspf_track **track)
{
	xspf_track *ret;

	ret = new xspf_track;
	ret->creator = NULL;
	ret->title = NULL;
	ret->album = NULL;
	ret->duration = -1;
	ret->tracknum = -1;
	ret->locations = NULL;
	ret->identifiers = NULL;
	ret->pdata = NULL;
	ret->next = *track;
	*track = ret;

	return (ret);
}

int
xspf_write(struct xspf_list *list, char const *filename, char const *baseuri)
{
	xspf_track *strack;
	xspf_mvalue *smvalue;
	XspfIndentFormatter formatter(-2);
	int error;
	XspfWriter * const writer = XspfWriter::makeWriter(formatter,
			baseuri, XspfWriter::NO_XML_BASE, &error);
	if (writer == NULL) {
		return error;
	}

	/* Playlist properties */
	{
		XspfProps props;
		props.lendLicense(list->license);
		props.lendLocation(list->location);
		props.lendIdentifier(list->identifier);
		writer->setProps(props);
	}

	XSPF_LIST_FOREACH_TRACK(list, strack) {
		/* Tracks */
		XspfTrack track;
		track.lendCreator(strack->creator);
		track.lendTitle(strack->title);
		track.lendAlbum(strack->album);
		track.setDuration(strack->duration);
		track.setTrackNum(strack->tracknum);

		/* Track locations and identifiers */
		XSPF_TRACK_FOREACH_LOCATION(strack,smvalue)
			track.lendAppendLocation(smvalue->value);
		XSPF_TRACK_FOREACH_IDENTIFIER(strack, smvalue)
			track.lendAppendIdentifier(smvalue->value);

		writer->addTrack(track);
	}

	int const res = writer->writeFile(filename);
	delete writer;
	return res;
}
