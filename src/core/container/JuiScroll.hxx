�}q    �����2��Ȝ]	0���
Tmć*ňww+  ƀ��RL~���b����0eFAl�!&�j��@�6̣~ݱ��d$��ˮ^�f�I-�uD�YL��4�����^v=�q��M�����f��Pny��A�7�tl�l�r���l�n3mQG�~\���x\���=���[t6����9Z��ʥ�'q�,ʓ�V%�Y��m<�!��L����{�}��+*�Ɵ���Ʀ����̷Rv���a��� �Nm
o�|�d�����.�<.�
��5�K������{[�H̤�C�K�-5[���=l��[�����e^�ټ�T-ʘn�hљ�����ں�T��-��p��c��/��B�Nw��*�9f�>&���jd:K�7=��s��NR���l7KPF�Ʊ?Y(�F^��	S�N�z?�O�����31�k!Ez�|�adaVWO%w�픚CT�<�N�t\�xj:]���FS|M��4��l!P沑�|A_�q��}ץ\s�oint2I offset, const JRectI& rcPaint);
	virtual void UpdateLayout(const JRectI& newRect);

	virtual void DrawVScrollBar(const JPoint2I &offset);
	virtual void DrawHScrollBar(const JPoint2I &offset);

protected:
	bool CalcChildExtent();

protected:
	JPoint2I m_ptChildPos;
	JPoint2I m_ptChildExtent;

	JPoint2I m_ptContentExtent;

	bool m_bAutoHide;
	bool m_bVertBar;
	bool m_bHorizBar;

	JImage *m_pBarImg;
	JImage *m_pArrowImg;
};

#endif